/* See LICENSE file for copyright and license details. */

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

#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          SHCMD("dmenu_run") },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("dmenu-arch-wiki-searcher") },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },

    { MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },
    { MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("$BROWSER --profile ~/.librewolf/cihrbns7.Normie") },
    { MODKEY|ShiftMask|ControlMask, XK_w,      spawn,          SHCMD("$BROWSER --profile ~/.librewolf/cihrbns7.Normie --private-window") },
    { MODKEY|ShiftMask,				XK_s,	   spawn,	   	   SHCMD("steam") },
    { MODKEY|ShiftMask,				XK_d,	   spawn,	   	   SHCMD("discord") },
    { MODKEY|ShiftMask|ControlMask,	XK_o,	   spawn,	   	   SHCMD("idea") },
    { MODKEY,                       XK_e,      spawn,          SHCMD(TERMINAL " -e neomutt; pkill -RTMIN+11 dwmblocks") },
    { MODKEY,                       XK_r,      spawn,          SHCMD(TERMINAL " -e lfub") },
    { MODKEY|ShiftMask,             XK_r,      spawn,          SHCMD(TERMINAL " -e htop") },
    { MODKEY,             			XK_t,      spawn,          SHCMD("keepassxc") },
    { MODKEY|ShiftMask,             XK_t,      spawn,          SHCMD("thinkorswim") },
    { MODKEY|ShiftMask,            	XK_t,      spawn,          SHCMD("keepassxc") },
    { MODKEY,                       XK_u,      spawn,          SHCMD(TERMINAL " -e newsboat") },
    { MODKEY,                       XK_o,      spawn,          SHCMD(TERMINAL " -e yay -Syu; pkill -RTMIN+10 dwmblocks") },
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

    { MODKEY,                       XK_F9,     spawn,          SHCMD("wall-d -p -f -d $XDG_PICTURES_DIR/desktop-backgrounds") }, // Change wallpapers
    { MODKEY|ShiftMask,             XK_F9,     spawn,          SHCMD("wall-d -p -f -o -d $XDG_PICTURES_DIR/desktop-backgrounds") }, // Change wallpapers with options
    { MODKEY,                       XK_F10,    spawn,          SHCMD("dmenu-config-dir") }, // Open config dirs
    { MODKEY|ShiftMask,             XK_F10,    spawn,          SHCMD(TERMINAL " -e dmenu-picture-dir") }, // Open config dirs
    { MODKEY,                       XK_F11,    spawn,          SHCMD("dmenu-mount") }, // Mount Drives
    { MODKEY|ShiftMask,             XK_F11,    spawn,          SHCMD("dmenu-umount") }, // Unmount Drives
    { MODKEY|ControlMask|ShiftMask, XK_F11,    spawn,          SHCMD("dmenu-unicode") }, // Copy unicode characters
    { MODKEY,                       XK_F12,    spawn,          SHCMD(TERMINAL " -e pulsemixer; pkill -RTMIN+8 dwmblocks") }, // Volume
    { 0,                       		XK_Print,  spawn,          SHCMD("maim -q -d 0.2 \"$XDG_PICTURES_DIR/screenshots/$(date '+%Y-%m-%d_%H:%M:%S').png\"; notify-send 'Maim Screenshots' 'Screenshot saved!'") }, // Screenshots
    { MODKEY,                       XK_Print,  spawn,          SHCMD("dmenu-maim") },
    { MODKEY|ShiftMask,             XK_Print,  spawn,          SHCMD("daytrade-screenshot") },
	{ MODKEY,						XK_minus,  spawn,		   SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; pkill -RTMIN+8 dwmblocks") },
	{ MODKEY|ShiftMask,				XK_minus,  spawn,		   SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%-; pkill -RTMIN+8 dwmblocks") },
	{ MODKEY,						XK_equal,  spawn,		   SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; pkill -RTMIN+8 dwmblocks") },
	{ MODKEY|ShiftMask,				XK_equal,  spawn,		   SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%+; pkill -RTMIN+8 dwmblocks") },
	{ MODKEY,				  XK_Scroll_Lock,  spawn,		   SHCMD("killall screenkey || screenkey &") },
	{ MODKEY,						XK_F6,	   spawn,		   SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam --autofit=100%x480 --demuxer-lavf-o-set=input_format=mjpeg $(ls /dev/video[0,2,4,6,8] | tail -n 2)") },
	/*{ MODKEY,						XK_F6,	   spawn,		   SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam --autofit=100%x480 $(ls /dev/video[0,2,4,6,8] | tail -n 1)") }, */

	{ MODKEY|ShiftMask,             XK_q,      quit,          {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,          {1} }, 
    { MODKEY,             			XK_Delete, spawn,         SHCMD("dmenu-system") },
    { MODKEY|ShiftMask,             XK_Delete, spawn,         SHCMD("reboot") },
    { MODKEY|ControlMask|ShiftMask, XK_Delete, spawn,         SHCMD("poweroff") },

	{ 0,	XF86XK_AudioMute,		 		   spawn,		   SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; pkill -RTMIN+8 dwmblocks") },
	{ 0,	XF86XK_AudioRaiseVolume, 		   spawn,		   SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%- && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%+; pkill -RTMIN+8 dwmblocks") },
	{ 0,	XF86XK_AudioLowerVolume, 		   spawn,		   SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%+ && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%-; pkill -RTMIN+8 dwmblocks") },
	{ 0, XF86XK_AudioPrev,		 			   spawn,		   {.v = (const char*[]){ "mpc", "prev", NULL } } },
	{ 0, XF86XK_AudioNext,		 			   spawn,		   {.v = (const char*[]){ "mpc",  "next", NULL } } },
	{ 0, XF86XK_AudioPause,		 			   spawn,		   {.v = (const char*[]){ "mpc", "pause", NULL } } },
	{ 0, XF86XK_AudioPlay,		 			   spawn,		   {.v = (const char*[]){ "mpc", "play", NULL } } },
	{ 0, XF86XK_AudioStop,		 			   spawn,		   {.v = (const char*[]){ "mpc", "stop", NULL } } },
	{ 0, XF86XK_AudioRewind,		       	   spawn,		   {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	{ 0, XF86XK_AudioForward,	       		   spawn,		   {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
	{ 0, XF86XK_AudioMedia,		 	      	   spawn,		   {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	{ 0, XF86XK_AudioMicMute,	       		   spawn,		   SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	/* { 0, XF86XK_PowerOff,				   spawn,		   {.v = (const char*[]){ "sysact", NULL } } }, */
	{ 0, XF86XK_Calculator,					   spawn,		   {.v = (const char*[]){ TERMINAL, "-e", "bc", "-l", NULL } } },
	{ 0, XF86XK_Sleep,						   spawn,		   {.v = (const char*[]){ "sudo", "-A", "zzz", NULL } } },
	{ 0, XF86XK_WWW,						   spawn,		   SHCMD("$BROWSER") },
	{ 0, XF86XK_DOS,						   spawn,		   {.v = termcmd } },
	{ 0, XF86XK_ScreenSaver,				   spawn,		   SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,					   spawn,		   {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	{ 0, XF86XK_Mail,						   spawn,		   SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+11 dwmblocks") },
	{ 0, XF86XK_MyComputer,					   spawn,		   {.v = (const char*[]){ TERMINAL, "-e",  "lfub",  "/", NULL } } },
	/* { 0, XF86XK_Battery,					   spawn,		   SHCMD("") }, */
	{ 0, XF86XK_Launch1,					   spawn,		   {.v = (const char*[]){ "xset", "dpms", "force", "off", NULL } } },
	{ 0, XF86XK_TouchpadToggle,				   spawn,		   SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,				   spawn,		   {.v = (const char*[]){ "synclient", "TouchpadOff=1", NULL } } },
	{ 0, XF86XK_TouchpadOn,					   spawn,		   {.v = (const char*[]){ "synclient", "TouchpadOff=0", NULL } } },
	{ 0, XF86XK_MonBrightnessUp,			   spawn,		   {.v = (const char*[]){ "xbacklight", "-inc", "15", NULL } } },
	{ 0, XF86XK_MonBrightnessDown,			   spawn,		   {.v = (const char*[]){ "xbacklight", "-dec", "15", NULL } } },
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
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
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
