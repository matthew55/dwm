/* See LICENSE file for copyright and license details. */

#define TERMINAL "st" /* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char *fonts[]            = { "monospace:size=10", "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true", "Unifont::pixelsize=10:antialias=true:autohint=true" };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
 };

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */
	{ "[@]",	spiral },		/* Fibonacci spiral */

	{ "[]=",	tile },			/* Default: Master on left, slaves on right */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */

	{ "[D]",	deck },			/* Master on left, slaves in monocle-like mode on right */
	{ "[M]",	monocle },		/* All windows on top of eachother */

	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */

	{ "><>",	NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL },};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          SHCMD("dmenu_run") },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("dmenu-arch-wiki-searcher") },
	{ MODKEY|ControlMask|ShiftMask, XK_p,      spawn,          SHCMD("dmenu-artix-wiki-searcher") },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },

        { MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },
        { MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("$BROWSER --profile ~/.mozilla/firefox/51ufyvxx.Normie") },
        { MODKEY|ShiftMask,		XK_s,	   spawn,	   SHCMD("steam") },
        { MODKEY|ShiftMask,		XK_d,	   spawn,	   SHCMD("discord") },
        { MODKEY,                       XK_r,      spawn,          SHCMD(TERMINAL " -e ranger") },
        { MODKEY|ShiftMask,             XK_r,      spawn,          SHCMD(TERMINAL " -e htop") },
        { MODKEY|ControlMask|ShiftMask, XK_r,      spawn,          SHCMD(TERMINAL " -e ranger --choosedir=$(pwd)") },
        { MODKEY,                       XK_o,      spawn,          SHCMD(TERMINAL " -e yay -Syyu") },
        { MODKEY|ShiftMask,             XK_o,      spawn,          SHCMD("idea") }, // Intellij
        { MODKEY,                       XK_e,      spawn,          SHCMD("warp-cli enable-always-on") },
        { MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("warp-cli disable-always-on") },

	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      incrgaps,       {.i = +3 } },
	{ MODKEY|ShiftMask,             XK_z,      incrgaps,       {.i = -3 } },
	{ MODKEY,			XK_a,	   togglegaps,     {0} },
	{ MODKEY|ShiftMask,		XK_a,	   defaultgaps,	   {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },

	{ MODKEY,			XK_y,	   setlayout,      {.v = &layouts[0]} }, /* dwindle */
	{ MODKEY|ShiftMask,		XK_y,	   setlayout,	   {.v = &layouts[1]} }, /* tile */
	{ MODKEY,			XK_t,	   setlayout,	   {.v = &layouts[2]} }, /* tile */
	{ MODKEY|ShiftMask,		XK_t,	   setlayout,	   {.v = &layouts[3]} }, /* bstack */
	{ MODKEY,			XK_u,	   setlayout,	   {.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,		XK_u,	   setlayout,	   {.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			XK_i,	   setlayout,	   {.v = &layouts[6]} }, /*centeredmaster */
	{ MODKEY|ShiftMask,		XK_i,	   setlayout,	   {.v = &layouts[7]} }, /* centeredfloatingmaster */	
	{ MODKEY|ShiftMask,		XK_f,	   setlayout,	   {.v = &layouts[8]} }, /* fullfloating */	

	{ MODKEY,			XK_f,	   togglefullscr,  {0} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
        { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,			XK_s,	   togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,      shiftview,      {.i = +1 } },
	{ MODKEY,                       XK_b,      shiftview,      {.i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

        { MODKEY,                       XK_F10,    spawn,         SHCMD("dmenu-config-dir") }, // Mount Drives
        { MODKEY|ShiftMask,             XK_F10,    spawn,         SHCMD("dmenu-wallpapers") }, // Mount Drives
        { MODKEY,                       XK_F11,    spawn,         SHCMD("dmenu-mount") }, // Mount Drives
        { MODKEY|ShiftMask,             XK_F11,    spawn,         SHCMD("dmenu-umount") }, // Unmount Drives
        { MODKEY|ShiftMask|ControlMask, XK_F11,    spawn,         SHCMD("dmenu-unicode") }, // Unmount Drives
        { MODKEY,                       XK_F12,    spawn,         SHCMD(TERMINAL " -e pulsemixer") }, // Volume
        { MODKEY,                       XK_Print,  spawn,          SHCMD("deepin-screenshot") }, // Screenshots

	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
        { MODKEY,                       XK_Delete, spawn,          SHCMD("sudo poweroff") },
        { MODKEY|ShiftMask,             XK_Delete, spawn,          SHCMD("sudo reboot") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e vim ~/.config/dwmblocks/config.h") },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
	/* signum       function        argument  */
	{ 1,            xrdb,           {.v = NULL } },
	{ 2,            setlayout,      {.v = &layouts[1]} },
};
