/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;	/* 1 means swallow floating windows by default */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int horizpadbar        = 0;        /* horizontal padding for statusbar */
static const int vertpadbar         = 0;        /* vertical padding for statusbar */
static const char *fonts[]          = { "iosevka:size=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "iosevka:size=10:antialias=true:autohint=true";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#bbbbbb", "#000000", "#444444" },
	[SchemeSel]  = { "#eeeeee", "#005577", "#005577" },
};

/* tagging */
static const char *tags[] = { "M", "o", "e", "c", "h", "a", "o", "!" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  iscentered  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         0,	      1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,	      0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,	      0,          1,           0,        -1 },
	{ "Zathura", NULL,     NULL,           0,         0,	      0,          0,           0,        -1 },
	{ "Sxiv",    NULL,     NULL,           0,         0,	      0,          0,           0,        -1 },
	{ "mpv",     NULL,     NULL,           0,         1,	      1,          0,           1,        -1 },
	{ "termapp", NULL,     NULL,           0,         1,	      1,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,	      0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hint */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[ ]",      tile },    /* first entry is default */
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", "#000000", "-nf", "#bbbbbb", "-sb", "#005577", "-sf", "#eeeeee", NULL };
static const char *termcmd[]  = { "st", "-e", NULL };
static const char *firefox[] = { "firefox", "-e", NULL };
static const char *ncmpcpp[] = { "st", "-e", "ncmpcpp", NULL };
static const char *pulsemixer[] = { "st", "-c", "termapp", "-g", "100x25", "-e", "pulsemixer", NULL };
static const char *lf[] = { "st", "-e", "lfub", NULL };
static const char *htop[] = { "st", "-c", "termapp", "-g", "100x25", "-e", "htop", NULL };
static const char *trackma[] = { "st", "-e", "trackma-curses", NULL };
static const char *anicli[] = { "st", "-c", "termapp", "-g", "100x25", "-e", "ani-cli", "-q", "best", NULL };
static const char *nmtui[] = { "st", "-c", "termapp", "-g", "100x25", "-e", "nmtui", NULL };
static const char *tremc[] = { "st", "-c", "termapp", "-g", "100x25", "-e", "tremc", NULL };
static const char *passmenu[] = { "passmenu", "-c", NULL };

#include "movestack.c"
#include "shiftview.c"
#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        		function        argument */
	/* Unused keys: t, s, g, */
	/* Programs */
	{ MODKEY,                       XK_d,      			spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_d,      			spawn,          SHCMD("cat ~/.local/share/key | dmenu -c -i -l 39") },
	{ MODKEY,	                XK_Return, 			spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,	        XK_Return, 			spawn,          SHCMD("st -c termapp -g 100x25") },
//	{ MODKEY,			XK_e,	   			spawn,	   	SHCMD("emacsclient -c -a 'emacs'") },
	{ MODKEY,	       		XK_p,      			spawn,          {.v = passmenu } },
	{ MODKEY,	       		XK_c,      			spawn,          {.v = tremc } },
	{ MODKEY,	                XK_w,      			spawn,          {.v = firefox } },
	{ MODKEY|ShiftMask,	        XK_w,      			spawn,          {.v = nmtui } },
	{ MODKEY,	       		XK_m,      			spawn,          {.v = ncmpcpp } },
	{ MODKEY|ShiftMask,	       	XK_m,      			spawn,          {.v = pulsemixer } },
	{ MODKEY,	       		XK_r,      			spawn,          {.v = lf } },
	{ MODKEY|ShiftMask,	       	XK_r,      			spawn,          {.v = htop } },
	{ MODKEY,	       		XK_a,      			spawn,          {.v = anicli } },
	{ MODKEY|ShiftMask,	       	XK_a,      			spawn,          {.v = trackma } },

	/* Audio Controls */
	{ MODKEY,	       		XK_equal,   			spawn,          SHCMD("pamixer --allow-boost -i 5; ~/.local/bin/killbar") },
	{ MODKEY|ShiftMask,	       	XK_equal,   			spawn,          SHCMD("pamixer --allow-boost -i 15; ~/.local/bin/killbar") },
	{ MODKEY,	       		XK_minus,   			spawn,          SHCMD("pamixer --allow-boost -d 5; ~/.local/bin/killbar") },
	{ MODKEY|ShiftMask,	       	XK_minus,   			spawn,          SHCMD("pamixer --allow-boost -d 15; ~/.local/bin/killbar") },
	{ MODKEY|ControlMask,	       	XK_m,   			spawn,          SHCMD("pamixer -t; ~/.local/bin/killbar") },
	
	/* MPD Controls */
	{ MODKEY,	       		XK_period,   			spawn,          SHCMD("~/.local/bin/mpcnext") },
	{ MODKEY|ShiftMask,	       	XK_period,   			spawn,          SHCMD("mpc repeat") },
	{ MODKEY,	       		XK_comma,   			spawn,          SHCMD("~/.local/bin/mpcprev") },
	{ MODKEY|ShiftMask,	       	XK_comma,   			spawn,          SHCMD("mpc seek 0%") },
	{ MODKEY,	       		XK_p,   			spawn,          SHCMD("~/.local/bin/mpctoggle") },
	{ MODKEY|ShiftMask,	       	XK_p,   			spawn,          SHCMD("mpc pause; pauseallmpv") },
	{ MODKEY,	       		XK_bracketleft, 		spawn,          SHCMD("mpc seek -10") },
	{ MODKEY|ShiftMask,	       	XK_bracketleft, 		spawn,          SHCMD("mpc seek -60") },
	{ MODKEY,	       		XK_bracketright,		spawn,          SHCMD("mpc seek +10") },
	{ MODKEY|ShiftMask,	       	XK_bracketright, 		spawn,          SHCMD("mpc seek +60") },
	
	/* Utilities */
	{ MODKEY,	       		XK_BackSpace,   		spawn,          SHCMD("~/.local/bin/power") },
	{ MODKEY|ShiftMask,	       	XK_BackSpace,   		spawn,          SHCMD("~/.local/bin/power") },
	{ MODKEY,	       		XK_F1,   			spawn,          SHCMD("~/.local/bin/dmenu-mount") },
	{ MODKEY|ShiftMask,	       	XK_F1,   			spawn,          SHCMD("~/.local/bin/dmenu-umount") },
	{ MODKEY,	       		XK_Delete,   			spawn,          SHCMD("~/.local/bin/screencapturearea") },
	{ MODKEY|ShiftMask,	       	XK_Delete,   			spawn,          SHCMD("~/.local/bin/screencaptureroot") },
	{ 0,	       			XF86XK_MonBrightnessUp, 	spawn,          SHCMD("xbacklight -inc 15") },
	{ MODKEY,	       		XF86XK_MonBrightnessUp, 	spawn,          SHCMD("xbacklight -inc 5") },
	{ 0,	       			XF86XK_MonBrightnessDown,	spawn,          SHCMD("xbacklight -dec 15") },
	{ MODKEY,	       		XF86XK_MonBrightnessDown,	spawn,          SHCMD("xbacklight -dec 15") },

	/* Layouts */
	{ MODKEY,                       XK_y,      			setlayout,      {.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,             XK_y,      			setlayout,      {.v = &layouts[1]} }, /* bstack */
	{ MODKEY|ControlMask,           XK_y,      			setlayout,      {.v = &layouts[2]} }, /* bstack horizontal */
	{ MODKEY|ShiftMask,             XK_u,      			setlayout,      {.v = &layouts[3]} }, /* centered master */
	{ MODKEY,             		XK_u,      			setlayout,      {.v = &layouts[4]} }, /* centered floating master */
	{ MODKEY|ShiftMask,             XK_i,      			setlayout,      {.v = &layouts[5]} }, /* monocle */
	{ MODKEY|ShiftMask,             XK_i,      			setlayout,      {.v = &layouts[6]} }, /* float */
	{ MODKEY|ControlMask,           XK_i,  				togglefloating, {0} },

	/* Gaps */
	{ MODKEY,              		XK_z,      			incrgaps,       {.i = +5 } },
	{ MODKEY,              		XK_x,      			incrgaps,       {.i = -5 } },
	{ MODKEY,              		XK_grave,      			togglegaps,     {0} },
	{ MODKEY|ShiftMask,    		XK_grave,      			defaultgaps,    {0} },

	/* DWM General Controls */
	{ MODKEY,                       XK_b,      			togglebar,      {0} },
	{ MODKEY,			XK_s,				togglesticky,   {0} },
	{ MODKEY,			XK_f,				togglefullscr,  {0} },
	{ MODKEY,                       XK_space, 			zoom,           {0} },
	{ MODKEY,                       XK_Tab,    			view,           {0} },
	{ MODKEY,             		XK_q,      			killclient,     {0} },
	{ MODKEY,                       XK_j,      			focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      			focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      			movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      			movestack,      {.i = -1 } },
	{ MODKEY,                       XK_o,      			incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      			incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      			setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      			setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_j,   			moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY|ControlMask,           XK_k,     			moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY|ControlMask,           XK_l,  				moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY|ControlMask,           XK_h,   			moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|Mod1Mask,              XK_j,   			moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|Mod1Mask,              XK_k,     			moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|Mod1Mask,              XK_l,  				moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|Mod1Mask,              XK_h,   			moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY,                       XK_Left,  			focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_Right, 			focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,  			tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right, 			tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      			shiftview,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,      			shiftview,      {.i = -1 } },
	TAGKEYS(                        XK_1,      	                0)
	TAGKEYS(                        XK_2,      	                1)
	TAGKEYS(                        XK_3,           	        2)
	TAGKEYS(                        XK_4,           	        3)
	TAGKEYS(                        XK_5,           	        4)
	TAGKEYS(                        XK_6,           	        5)
	TAGKEYS(                        XK_7,           	        6)
	TAGKEYS(                        XK_8,           	        7)
	TAGKEYS(                        XK_9,          	 	        8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

