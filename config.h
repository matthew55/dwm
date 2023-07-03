/* See LICENSE file for copyright and license details. */

// Include extra buttons such as XF86AudioRaiseVolume and others.
#include <X11/XF86keysym.h>

#define TERMINAL "st"
/* appearance */
static const unsigned int borderpx    = 2;        /* border pixel of windows */
static const unsigned int snap        = 32;       /* snap pixel */
static const unsigned int gappih      = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv      = 10;       /* vert inner gap between windows */
static const unsigned int gappoh      = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov      = 30;       /* vert outer gap between windows and screen edge */
static const unsigned int iconsize    = 16;   	  /* icon size */
static const unsigned int iconspacing = 8; 	  /* space between icon and title */
static       int smartgaps            = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar              = 1;        /* 0 means no bar */
static const int topbar               = 1;        /* 0 means bottom bar */
static char *fonts[]                  = { 
    "monospace:size=13", 
    "NotoColorEmoji:pixelsize=13:antialias=ture:autohint=true",  
};
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
	/* class      		instance    title      			 tags mask     isfloating   monitor */
	{ "Gimp",     		NULL,       NULL,      			 0,            1,           -1 },
	{ "Nsxiv",     		"nsxiv",    NULL,      			 0,            1,           -1 },
	{ "Firefox",  		NULL,       NULL,      			 1 << 8,       0,           -1 },
	{ "Tor Browser",	NULL,       NULL,      			 0,       	   1,           -1 },
	{ "mpv",			NULL,		NULL, 				 0,       	   1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
        /* first entry is default */
	{ "[]=",	tile },			          /* Default: Master on left, slaves on right */
	{ "[M]",	monocle },		          /* All windows on top of eachother */
	{ "[@]",	spiral },		          /* Fibonacci spiral */
	{ "[\\]",	dwindle },		          /* Decreasing in size right and leftward */
	{ "H[]",	deck },			          /* Master on left, slaves in monocle-like mode on right */
	{ "TTT",    bstack },		          /* Master on top, slaves on bottom */
	{ "HHH",    gaplessgrid },            /* Master on top left, slaves follow verticle grid */
	{ "###",    nrowgrid },               /* Same but horizontal grid */
	{ "|M|",	centeredmaster },		  /* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster }, /* Same but master floats */
	{ "><>",    NULL },                   /* no layout function means floating behavior */
	{ NULL,     NULL },                   /* Needed for cycling to work */
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTMOD Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
    { ALTMOD,                       KEY,      focusnthmon,    {.i  = TAG } }, \
    { ALTMOD|ShiftMask,             KEY,      tagnthmon,      {.i  = TAG } },

#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, 
	/*{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },*/

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          SHCMD("dmenu_run") },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("dmenu-arch-wiki-searcher") },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },

    { MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },
    { MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("$BROWSER --profile ~/.mozilla/firefox/hz1axv5p.Normie") },
    { MODKEY|ShiftMask,				XK_s,	   spawn,	   	   SHCMD("steam") },
    { MODKEY|ShiftMask,				XK_d,	   spawn,	   	   SHCMD("discord") },
    { MODKEY|ShiftMask|ControlMask,	XK_o,	   spawn,	   	   SHCMD("idea") },
    { MODKEY,                       XK_e,      spawn,          SHCMD(TERMINAL " -e neomutt") },
    { MODKEY,                       XK_r,      spawn,          SHCMD(TERMINAL " -e lfub") },
    { MODKEY|ShiftMask,             XK_r,      spawn,          SHCMD(TERMINAL " -e htop") },
    { MODKEY,             			XK_t,      spawn,          SHCMD("keepassxc") },
    { MODKEY|ShiftMask,             XK_t,      spawn,          SHCMD("thinkorswim") },
    { MODKEY|ShiftMask,            	XK_t,      spawn,          SHCMD("keepassxc") },
    { MODKEY,                       XK_o,      spawn,          SHCMD(TERMINAL " -e yay -Syu && pkill -RTMIN+10 \"${STATUSBAR:-dwmblocks}\"") },
    { MODKEY|ShiftMask,             XK_o,      spawn,          SHCMD(TERMINAL " -e ping 1.1.1.1") },

    { MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      incrgaps,       {.i = +3 } },
	{ MODKEY|ShiftMask,             XK_z,      incrgaps,       {.i = -3 } },
	{ MODKEY,						XK_a,	   togglegaps,     {0} },
	{ MODKEY|ShiftMask,				XK_a,	   defaultgaps,	   {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },

	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
    { MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask,			XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
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

    { MODKEY,                       XF86XK_MonBrightnessDown,  spawn,          SHCMD("wall-d -p -f -d ~/Pictures/desktop-backgrounds") }, // Change wallpapers
    { MODKEY|ShiftMask,             XF86XK_MonBrightnessDown,  spawn,          SHCMD("wall-d -p -f -o -d ~/Pictures/desktop-backgrounds") }, // Change wallpapers with options
    { MODKEY,                       XF86XK_MonBrightnessUp,    spawn,          SHCMD("dmenu-config-dir") }, // Open config dirs
    { MODKEY|ShiftMask,             XF86XK_MonBrightnessUp,    spawn,          SHCMD(TERMINAL " -e dmenu-picture-dir") }, // Open config dirs
    { MODKEY,                       XF86XK_AudioLowerVolume,   spawn,          SHCMD("dmenu-mount") }, // Mount Drives
    { MODKEY|ShiftMask,             XF86XK_AudioLowerVolume,   spawn,          SHCMD("dmenu-umount") }, // Unmount Drives
    { MODKEY|ControlMask|ShiftMask, XF86XK_AudioLowerVolume,   spawn,          SHCMD("dmenu-unicode") }, // Copy unicode characters
    { MODKEY,                       XF86XK_AudioRaiseVolume,   spawn, 		   SHCMD(TERMINAL " -e pulsemixer") }, // Volume
    { MODKEY,                       XK_Print,  spawn,         				   SHCMD("deepin-screenshot") }, // Screenshots
	{ 0	,							XF86XK_AudioMute,    	   spawn,		   SHCMD("pamixer -t; pkill -RTMIN+8 ${STATUSBAR:-dwmblocks} >/dev/null") },
	{ 0	,							XF86XK_AudioLowerVolume,   spawn,		   SHCMD("pamixer --allow-boost -d 5; pkill -RTMIN+8 ${STATUSBAR:-dwmblocks} >/dev/null") },
	{ ShiftMask,				    XF86XK_AudioLowerVolume,   spawn,		   SHCMD("pamixer --allow-boost -d 15; pkill -RTMIN+8 ${STATUSBAR:-dwmblocks} >/dev/null") },
	{ 0,							XF86XK_AudioRaiseVolume,   spawn,		   SHCMD("pamixer --allow-boost -i 5; pkill -RTMIN+8 ${STATUSBAR:-dwmblocks} >/dev/null") },
	{ ShiftMask,					XF86XK_AudioRaiseVolume,   spawn,		   SHCMD("pamixer --allow-boost -i 15; pkill -RTMIN+8 ${STATUSBAR:-dwmblocks} >/dev/null") },

	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
    { MODKEY,                       XK_Delete, spawn,          SHCMD("sudo poweroff") },
    { MODKEY|ShiftMask,             XK_Delete, spawn,          SHCMD("sudo reboot") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e vim ~/.config/dwmblocks/config.h") },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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
};
