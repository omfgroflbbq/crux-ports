  /* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-gohu-gohufont-medium-*-*-*-11-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#000000";
static const char normbgcolor[]     = "#000000";
static const char normfgcolor[]     = "#969896";
static const char selbordercolor[]  = "#b5bd68";
static const char selbgcolor[]      = "#1c1c1c";
static const char selfgcolor[]      = "#b5bd68";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "Misc", "WWW", "IM", "Media", "Dev", "VMs", "Rss" };

static const Rule rules[] = {
  /* class  instance    title       tags mask     isfloating   monitor */
  { "Firefox",  NULL,       NULL,       1 << 1,       False,      -1 },
};

/* layout(s) */
static const float mfact      = 0.5; /* factor of master area size [0.05..0.95] */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
  /* symbol arrange function */
  { "[T]",        tile },    /* first entry is default */
  { "[F]",        NULL },    /* no layout function means floating behavior */
  { "[M]",        monocle },
  { "[TTT]",      bstack },
  { "[===]",      bstackhoriz },
};

#include "X11/XF86keysym.h"

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
  { ControlMask,                  KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *urxvt[]  = { "urxvtc",      NULL };
static Key keys[] = {
  /* modifier                         key                       function    argument */
  { MODKEY|ControlMask,               XK_t,                     spawn,      { .v = urxvt } },
  { MODKEY|ControlMask,               XK_f,                     spawn,      SHCMD("firefox 2>&1 > /dev/null") },
  { Mod4Mask,                         XK_l,                     spawn,      SHCMD("slock") },
  { MODKEY|ControlMask,               XK_p,                     spawn,      SHCMD("scrot -d 0.00001 $HOME/'%d-%m-%Y %T.png'") },
  { 0,                                XF86XK_AudioRaiseVolume,  spawn,      SHCMD("amixer set Master 5%+ 2>&1 > /dev/null") },
  { 0,                                XF86XK_AudioLowerVolume,  spawn,      SHCMD("amixer set Master 5%- 2>&1 > /dev/null") },
  { 0,                                XF86XK_AudioMute,         spawn,      SHCMD("amixer set Master toggle 2>&1 > /dev/null") },
  { 0,                                XK_F7,                    spawn,      SHCMD("xrandr --output VGA --above LVDS --auto") },
  { Mod4Mask|ControlMask,             XK_h,                     view,     {0} },
  { Mod4Mask|ControlMask,             XK_l,                     view,     {0} },
  { MODKEY|ControlMask,               XK_b,                     togglebar,    {0} },
  { MODKEY,                           XK_Tab,                   focusstack,   {.i = +1 } },
  { MODKEY|ShiftMask,                 XK_Tab,                   focusstack,   {.i = -1 } },
  { Mod4Mask,                         XK_Tab,                   focusmon,   {.i = +1 } ,
  { Mod4Mask|ShiftMask,               XK_Tab,                   focusmon,   {.i = -1 } },
  { MODKEY,                           XK_comma,                 setmfact,   {.f = -0.05} },
  { MODKEY,                           XK_period,                setmfact,   {.f = +0.05} },
  { MODKEY,                           XK_F4,                    killclient,   {0} },
  { MODKEY,                           XK_Return,                zoom,     {0} },
  { MODKEY|ShiftMask,                 XK_t,                     setlayout,    {.v = &layouts[0]} },
  { MODKEY|ShiftMask,                 XK_f,                     setlayout,    {.v = &layouts[1]} },
  { MODKEY|ShiftMask,                 XK_m,                     setlayout,    {.v = &layouts[2]} },
  { MODKEY|ShiftMask,                 XK_g,                     setlayout,    {.v = &layouts[3]} },
  { MODKEY|ShiftMask,                 XK_v,                     setlayout,    {.v = &layouts[4]} },
  { MODKEY,                           XK_space,                 setlayout,    {0} },
  { Mod4Mask|ShiftMask,               XK_f,                     togglefloating,   {0} },
  { MODKEY|ControlMask,               XK_Left,                  cycle,      {.i = -1 } },
  { MODKEY|ControlMask,               XK_h,                     cycle,      {.i = -1 } },
  { MODKEY|ControlMask,               XK_Right,                 cycle,      {.i = +1 } },
  { MODKEY|ControlMask,               XK_l,                     cycle,      {.i = +1 } },
  TAGKEYS(                            XK_1,                     0)
  TAGKEYS(                            XK_2,                     1)
  TAGKEYS(                            XK_3,                     2)
  TAGKEYS(                            XK_4,                     3)
  TAGKEYS(                            XK_5,                     4)
  TAGKEYS(                            XK_6,                     5)
  TAGKEYS(                            XK_7,                     6)
  TAGKEYS(                            XK_8,                     7)
  TAGKEYS(                            XK_9,                     8)
  { MODKEY|ControlMask,               XK_BackSpace,             quit,     {0} },
  { MODKEY|ShiftMask,                 XK_j,     moveresize,     {.v = (int []){ 0, 25, 0, 0 }}},
  { MODKEY|ShiftMask,                 XK_k,     moveresize,     {.v = (int []){ 0, -25, 0, 0 }}},
  { MODKEY|ShiftMask,                 XK_l,     moveresize,     {.v = (int []){ 25, 0, 0, 0 }}},
  { MODKEY|ShiftMask,                 XK_h,     moveresize,     {.v = (int []){ -25, 0, 0, 0 }}},
  { MODKEY|ControlMask|ShiftMask,     XK_j,     moveresize,     {.v = (int []){ 0, 0, 0, 25 }}},
  { MODKEY|ControlMask|ShiftMask,     XK_k,     moveresize,     {.v = (int []){ 0, 0, 0, -25 }}},
  { MODKEY|ControlMask|ShiftMask,     XK_l,     moveresize,     {.v = (int []){ 0, 0, 25, 0 }}},
  { MODKEY|ControlMask|ShiftMask,     XK_h,     moveresize,     {.v = (int []){ 0, 0, -25, 0 }}},
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button2,        spawn,          { .v = urxvt} },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
