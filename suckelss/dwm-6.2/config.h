/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* volume control */
static const char *upvol[]   = { "amixer", "set", "Master", "10%+",     NULL };
static const char *downvol[] = { "amixer", "set", "Master", "10%-",     NULL };
static const char *mutevol[] = { "amixer", "set", "Master", "toggle", NULL };

/* screen brightness */
static const char *brup[] = { "brightnessctl", "set", "10%+", NULL };
static const char *brdown[] = { "brightnessctl", "set", "10%-", NULL };

/* ss */
static const char *sspy[] = {"ss-py", NULL};

/* monitor ex */
static const char *moff[] = {"monitor-off", NULL};
static const char *mon[] = {"monitor-on", NULL};

/* file manager */
static const char *fm[] = {"pcmanfm", NULL};

/* file manager */
static const char *nm[] = {"network", NULL};

/* browser */
static const char *browser[] = {"qutebrowser", NULL};

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int gappx	    = 1;	/* gap pixel betwen windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack Nerd Font::size=10:style=Bold" };
static const char dmenufont[]       = "Hack Nerd Font:size=10:style=Bold";
static const char col_gray[]       = "#dedede";
static const char col_blue[]        = "#315bef";
static const char col_red[]         = "#6d2115";
static const char col_dark[]       = "#37383b";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray, col_dark, col_blue },
	[SchemeSel]  = { col_gray, col_blue, col_blue },
};

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
   { "mpv", NULL, NULL, 0, 1, -1 },
   { "SimpleScreenRecorder", NULL, NULL, 0, 1, -1 },
   { "Lxappearance", NULL, NULL, 0, 1, -1 },
   { "qt5ct", NULL, NULL, 0, 1, -1 },
   { "Crow Translate", NULL, NULL, 0, 1, -1 },
   { "qView", NULL, NULL, 0, 1, -1 },
   { "Falkon", NULL, "Library", 0, 1, -1 },
   { "Xarchiver", NULL, NULL, 0, 1, -1 },
   { "System-config-printer.py", NULL, NULL, 0, 1, -1 },
   { "Nitrogen", NULL, NULL, 0, 1, -1 },
   { "st", NULL, "Youtube", 0, 1, -1 },
   { "st", NULL, "Musik", 0, 1, -1 },
   { "st", NULL, "Mixer", 0, 1, -1 },
   { "st", NULL, "cava", 0, 1, -1 },
   { "st", NULL, "a-clean", 0, 1, -1 },
   { "st", NULL, "Info Device", 0, 1, -1 },
   { "st", NULL, "PDF Merge", 0, 1, -1 },
   { "st", NULL, "Update System", 0, 1, -1 },
   { "st", NULL, "Terminal", 0, 1, -1 },
   { "st", NULL, "Network Manager", 0, 1, -1 },
   { "st", NULL, "File Manager", 0, 1, -1 },
   { "st", NULL, "N-TV", 0, 1, -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ " ",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_dark, "-nf", col_gray, "-sb", col_blue, "-sf", col_gray, "-p", "異 ", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *minitermcmd[]  = { "terminal", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,         XF86XK_AudioLowerVolume,      spawn, 	       {.v = downvol } },
	{ 0,                XF86XK_AudioMute,      spawn, 	       {.v = mutevol } },
	{ 0,         XF86XK_AudioRaiseVolume,      spawn, 	       {.v = upvol   } },
	{ 0, 		      XF86XK_MonBrightnessUp,      spawn,          {.v = brup} },
	{ 0, 		    XF86XK_MonBrightnessDown,      spawn,          {.v = brdown} },
	{ 0,				                XK_Print,      spawn,	         {.v = sspy} },
	{ 0,                      XK_Super_L,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = fm } },
	{ 0,                 XF86XK_HomePage,      spawn,          {.v = browser } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = minitermcmd } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = mon } },
	{ MODKEY|ShiftMask,             XK_o,      spawn,          {.v = moff } },
	{ MODKEY,                       XK_n,      spawn,          {.v = nm } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,            		        XK_x,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
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
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

