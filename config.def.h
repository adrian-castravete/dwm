/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gap between left-right windows and screen borders */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
	"DejaVu Sans:size=10:weight=bold:antialias=true:hinting=false:hintstyle=hintnone"
};
static const char dmenufont[]       = "DejaVu Sans:size=10:weight=bold:antialias=true:hinting=false:hintstyle=hintnone";
static const char col_nbg[]         = "#333333";
static const char col_nfg[]         = "#aaaaaa";
static const char col_nb[]          = "#555555";
static const char col_sbg[]         = "#508cd7";
static const char col_sfg[]         = "#dcf5ff";
static const char col_sb[]          = "#508cd7";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_nfg,   col_nbg,   col_nb },
	[SchemeSel]  = { col_sfg,   col_sbg,   col_sb },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class		instance    title       tags mask   monitor */
	{ "Gimp",		NULL,       NULL,       0,          -1 },
	{ "Chromium",		NULL,       NULL,       1 << 1,     -1 },
	{ "Firefox",		NULL,       NULL,       1 << 1,     -1 },
	{ "Firefox-esr",	NULL,       NULL,       1 << 1,     -1 },
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
static const char *dmenucmd[] = { "dmenu_run_history", "-p", "Run:", "-l", "10", "-m", dmenumon, "-fn", dmenufont, "-nb", col_nbg, "-nf", col_nfg, "-sb", col_sbg, "-sf", col_sfg, NULL };
static const char *filemgrcmd[] = { "pcmanfm", "-p", NULL };
static const char *termcmd[]  = { "x-terminal-emulator", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,                            XK_F1,     maximize,       {0} },
	{ 0,                            XK_F2,     maxleft,        {0} },
	{ 0,                            XK_F3,     maxright,       {0} },
	{ 0,                            XK_F4,     focusstack,     {.i = +1 } },
	{ ShiftMask,                    XK_F4,     focusstack,     {.i = -1 } },
	{ ControlMask,                  XK_F4,     zoom,           {0} },
	{ 0,                            XK_F6,     killclient,     {0} },
	{ 0,                            XK_F7,     focusmon,       {.i = +1 } },
	{ ControlMask,                  XK_F7,     focusmon,       {.i = -1 } },
	{ ShiftMask,                    XK_F7,     tagmon,         {.i = +1 } },
	{ ControlMask|ShiftMask,        XK_F7,     tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_l,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,      tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,      tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ 0,                            XK_F8,     spawn,          {.v = termcmd } },
	{ 0,                            XK_F10,    spawn,          {.v = filemgrcmd } },
	{ 0,                            XK_F12,    spawn,          {.v = dmenucmd } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

