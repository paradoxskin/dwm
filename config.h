#ifndef first
#include "dwm.c"
#endif
#define first
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 2;        /* gap pixel between windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "SauceCodePro Nerd Font:size=12:antialias=true:autohint=true", "Heiti J:size=12:antialias=true:autohint=true" };
static const char dmenufont[]       = "SauceCodePro Nerd Font:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_pink[]		= "#ff99cc";
static const char col_ice[]		    = "#57c6fe";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_pink  },
	[SchemeSelForze]  = { col_gray4, col_cyan,  col_ice  },
	[SchemeStatus]  = { col_gray3, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_ice, "#a86b90",  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]  = { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
	//[SchemeInfoSel]  = { "#dfcebf", "#40515e",  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoSel]  = { "#dfcebf", "#010101",  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm]  = { col_gray4, "#000000",  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, OPAQUE, borderalpha },
	[SchemeTagsSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsNorm]  = { OPAQUE, baralpha, borderalpha },
	[SchemeInfoSel]  = { OPAQUE, 0xaa,  borderalpha  },
	[SchemeInfoNorm]  = { OPAQUE, 0x00,  0x00  },
};

/* tagging */
static const char *tags[] = { "¹", "²", "³", "⁴󰲑", "五", "六", "七", "八", "⁹" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                  instance    title                                tags mask     isfloating   monitor */
	{ "firefox",              NULL,       NULL,                                1 << 2,       0,           -1 },
	{ "clash",                NULL,       NULL,                                1 << 8,       0,           -1 },
	{ "netease-cloud-music",  NULL,       NULL,                                1 << 3,       0,           -1 },
    { "float",                NULL,       NULL,                                0,            1,           -1 },
    { "float2",               NULL,       NULL,                                0,            2,           -1 },
    { "feh",                  NULL,       "feh [1 of 1] - /tmp/tmp.png",       0,            1,           -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	//{ "[]=",      tile },    /* first entry is default */
	//{ "<><",      NULL },    /* no layout function means floating behavior */
	{ "󱂫 ",      tile },    /* first entry is default */
	{ "󰘸 ",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG,cmd) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG, .v = cmd} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-l", "7", NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key putin_trigger = {MODKEY, XK_equal, switch_putin, {0}};
static const Key keys[] = {
	/* modifier                     key              function        argument */
	{ MODKEY,                       XK_p,            spawn,          {.v = dmenucmd } },
	{ MODKEY, 			            XK_Return,       spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_space,        spawn,          SHCMD("st -c float -A 0.5") },
	{ 0,                            XK_Print,        spawn,          SHCMD("~/.scripts/screenshot.sh") },
	{ MODKEY,                       XK_F2,           spawn,          SHCMD("~/.scripts/voltoggle.sh") },
	{ MODKEY,                       XK_F3,           spawn,          SHCMD("~/.scripts/voldown.sh") },
	{ MODKEY,                       XK_F4,           spawn,          SHCMD("~/.scripts/volup.sh") },
	{ MODKEY,                       XK_F5,           spawn,          SHCMD("~/.scripts/bgldown.sh") },
	{ MODKEY,                       XK_F6,           spawn,          SHCMD("~/.scripts/bglup.sh") },
	{ MODKEY,                       XK_F1,           spawn,          SHCMD("~/.scripts/switchtouchpad.sh") },
	{ MODKEY, 			            XK_o,            spawn,          SHCMD("~/.scripts/cgbg.sh") },
	{ MODKEY|ShiftMask,             XK_o,            spawn,          SHCMD("~/.scripts/cgwkbg.sh") },
	{ MODKEY, 			            XK_minus,            spawn,          SHCMD("~/.scripts/orangeScreen.sh") },
	{ MODKEY, 			            XK_backslash,    spawn,          SHCMD("~/.scripts/capture.sh") },
	{ MODKEY,                       XK_Delete,       spawn,          SHCMD("slock") },
	{ MODKEY,                       XK_b,            togglebar,      {0} },
	{ MODKEY,                       XK_j,            focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,            focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,            incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,            incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,            setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,            setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_s,            freeze,         {0} },
	{ MODKEY,                       XK_z,            zoom,           {0} },
	{ MODKEY,                       XK_Tab,          lastcli,        {0} },
	{ MODKEY,                       XK_comma,        goprevvis,        {0} },
	{ MODKEY,                       XK_period,       gonextvis,        {0} },
	{ MODKEY|ShiftMask,                       XK_comma,        goprev,        {0} },
	{ MODKEY|ShiftMask,                       XK_period,       gonext,        {0} },
	{ MODKEY, 			            XK_q,            killclient,     {0} },
	{ MODKEY,                       XK_t,            setlayout,      {.v = &layouts[0]} },
	//{ MODKEY,                       XK_f,            setlayout,      {.v = &layouts[1]} },
	//{ MODKEY,                       XK_m,            setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,        togglefloating, {0} },
	{ MODKEY,                       XK_0,            view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,            tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,        focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,       focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,        tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,       tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,            0,              0)
	TAGKEYS(                        XK_2,            1,              0)
	TAGKEYS(                        XK_3,            2,              0)
	TAGKEYS(                        XK_4,            3,              0)
	TAGKEYS(                        XK_5,            4,              0)
	TAGKEYS(                        XK_6,            5,              0)
	TAGKEYS(                        XK_7,            6,              0)
	TAGKEYS(                        XK_8,            7,              0)
	TAGKEYS(                        XK_9,            8,              0)
	TAGKEYS(                        XK_f,            2,              "firefox")
	TAGKEYS(                        XK_m,            3,              "spotify")
	//TAGKEYS(                        XK_m,            3,              "st -e ncspot")
	//TAGKEYS(                        XK_m,            3,              "st -A 0 -e '/home/paradoxd/.scripts/spotifyTUI.sh'")
	TAGKEYS(                        XK_v,            8,              "st -e '/home/paradoxd/.scripts/startvpn.sh'")
	{ MODKEY|ShiftMask,             XK_q,            quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          SHCMD("st -c float2 -e '/home/paradoxd/.bin/calendar'")},
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
