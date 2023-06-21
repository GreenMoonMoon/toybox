//
// Created by josue on 2023-06-21.
//

#ifndef TOYBOX_SRC_INTPUS_KEYCODE_H_
#define TOYBOX_SRC_INTPUS_KEYCODE_H_

typedef enum Keycode {
  PHYSICAL_KEY_UNKNOWN = 0,

  /**
   *  \name Usage page 0x07
   *
   *  These values are from usage page 0x07 (USB keyboard page).
   */
  /* @{ */

  PHYSICAL_KEY_A = 4,
  PHYSICAL_KEY_B = 5,
  PHYSICAL_KEY_C = 6,
  PHYSICAL_KEY_D = 7,
  PHYSICAL_KEY_E = 8,
  PHYSICAL_KEY_F = 9,
  PHYSICAL_KEY_G = 10,
  PHYSICAL_KEY_H = 11,
  PHYSICAL_KEY_I = 12,
  PHYSICAL_KEY_J = 13,
  PHYSICAL_KEY_K = 14,
  PHYSICAL_KEY_L = 15,
  PHYSICAL_KEY_M = 16,
  PHYSICAL_KEY_N = 17,
  PHYSICAL_KEY_O = 18,
  PHYSICAL_KEY_P = 19,
  PHYSICAL_KEY_Q = 20,
  PHYSICAL_KEY_R = 21,
  PHYSICAL_KEY_S = 22,
  PHYSICAL_KEY_T = 23,
  PHYSICAL_KEY_U = 24,
  PHYSICAL_KEY_V = 25,
  PHYSICAL_KEY_W = 26,
  PHYSICAL_KEY_X = 27,
  PHYSICAL_KEY_Y = 28,
  PHYSICAL_KEY_Z = 29,

  PHYSICAL_KEY_1 = 30,
  PHYSICAL_KEY_2 = 31,
  PHYSICAL_KEY_3 = 32,
  PHYSICAL_KEY_4 = 33,
  PHYSICAL_KEY_5 = 34,
  PHYSICAL_KEY_6 = 35,
  PHYSICAL_KEY_7 = 36,
  PHYSICAL_KEY_8 = 37,
  PHYSICAL_KEY_9 = 38,
  PHYSICAL_KEY_0 = 39,

  PHYSICAL_KEY_RETURN = 40,
  PHYSICAL_KEY_ESCAPE = 41,
  PHYSICAL_KEY_BACKSPACE = 42,
  PHYSICAL_KEY_TAB = 43,
  PHYSICAL_KEY_SPACE = 44,

  PHYSICAL_KEY_MINUS = 45,
  PHYSICAL_KEY_EQUALS = 46,
  PHYSICAL_KEY_LEFTBRACKET = 47,
  PHYSICAL_KEY_RIGHTBRACKET = 48,
  PHYSICAL_KEY_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
  PHYSICAL_KEY_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate PHYSICAL_KEY_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
  PHYSICAL_KEY_SEMICOLON = 51,
  PHYSICAL_KEY_APOSTROPHE = 52,
  PHYSICAL_KEY_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
  PHYSICAL_KEY_COMMA = 54,
  PHYSICAL_KEY_PERIOD = 55,
  PHYSICAL_KEY_SLASH = 56,

  PHYSICAL_KEY_CAPSLOCK = 57,

  PHYSICAL_KEY_F1 = 58,
  PHYSICAL_KEY_F2 = 59,
  PHYSICAL_KEY_F3 = 60,
  PHYSICAL_KEY_F4 = 61,
  PHYSICAL_KEY_F5 = 62,
  PHYSICAL_KEY_F6 = 63,
  PHYSICAL_KEY_F7 = 64,
  PHYSICAL_KEY_F8 = 65,
  PHYSICAL_KEY_F9 = 66,
  PHYSICAL_KEY_F10 = 67,
  PHYSICAL_KEY_F11 = 68,
  PHYSICAL_KEY_F12 = 69,

  PHYSICAL_KEY_PRINTSCREEN = 70,
  PHYSICAL_KEY_SCROLLLOCK = 71,
  PHYSICAL_KEY_PAUSE = 72,
  PHYSICAL_KEY_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
  PHYSICAL_KEY_HOME = 74,
  PHYSICAL_KEY_PAGEUP = 75,
  PHYSICAL_KEY_DELETE = 76,
  PHYSICAL_KEY_END = 77,
  PHYSICAL_KEY_PAGEDOWN = 78,
  PHYSICAL_KEY_RIGHT = 79,
  PHYSICAL_KEY_LEFT = 80,
  PHYSICAL_KEY_DOWN = 81,
  PHYSICAL_KEY_UP = 82,

  PHYSICAL_KEY_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
  PHYSICAL_KEY_KP_DIVIDE = 84,
  PHYSICAL_KEY_KP_MULTIPLY = 85,
  PHYSICAL_KEY_KP_MINUS = 86,
  PHYSICAL_KEY_KP_PLUS = 87,
  PHYSICAL_KEY_KP_ENTER = 88,
  PHYSICAL_KEY_KP_1 = 89,
  PHYSICAL_KEY_KP_2 = 90,
  PHYSICAL_KEY_KP_3 = 91,
  PHYSICAL_KEY_KP_4 = 92,
  PHYSICAL_KEY_KP_5 = 93,
  PHYSICAL_KEY_KP_6 = 94,
  PHYSICAL_KEY_KP_7 = 95,
  PHYSICAL_KEY_KP_8 = 96,
  PHYSICAL_KEY_KP_9 = 97,
  PHYSICAL_KEY_KP_0 = 98,
  PHYSICAL_KEY_KP_PERIOD = 99,

  PHYSICAL_KEY_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
  PHYSICAL_KEY_APPLICATION = 101, /**< windows contextual menu, compose */
  PHYSICAL_KEY_POWER = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
  PHYSICAL_KEY_KP_EQUALS = 103,
  PHYSICAL_KEY_F13 = 104,
  PHYSICAL_KEY_F14 = 105,
  PHYSICAL_KEY_F15 = 106,
  PHYSICAL_KEY_F16 = 107,
  PHYSICAL_KEY_F17 = 108,
  PHYSICAL_KEY_F18 = 109,
  PHYSICAL_KEY_F19 = 110,
  PHYSICAL_KEY_F20 = 111,
  PHYSICAL_KEY_F21 = 112,
  PHYSICAL_KEY_F22 = 113,
  PHYSICAL_KEY_F23 = 114,
  PHYSICAL_KEY_F24 = 115,
  PHYSICAL_KEY_EXECUTE = 116,
  PHYSICAL_KEY_HELP = 117,    /**< AL Integrated Help Center */
  PHYSICAL_KEY_MENU = 118,    /**< Menu (show menu) */
  PHYSICAL_KEY_SELECT = 119,
  PHYSICAL_KEY_STOP = 120,    /**< AC Stop */
  PHYSICAL_KEY_AGAIN = 121,   /**< AC Redo/Repeat */
  PHYSICAL_KEY_UNDO = 122,    /**< AC Undo */
  PHYSICAL_KEY_CUT = 123,     /**< AC Cut */
  PHYSICAL_KEY_COPY = 124,    /**< AC Copy */
  PHYSICAL_KEY_PASTE = 125,   /**< AC Paste */
  PHYSICAL_KEY_FIND = 126,    /**< AC Find */
  PHYSICAL_KEY_MUTE = 127,
  PHYSICAL_KEY_VOLUMEUP = 128,
  PHYSICAL_KEY_VOLUMEDOWN = 129,
/* not sure whether there's a reason to enable these */
/*     PHYSICAL_KEY_LOCKINGCAPSLOCK = 130,  */
/*     PHYSICAL_KEY_LOCKINGNUMLOCK = 131, */
/*     PHYSICAL_KEY_LOCKINGSCROLLLOCK = 132, */
  PHYSICAL_KEY_KP_COMMA = 133,
  PHYSICAL_KEY_KP_EQUALSAS400 = 134,

  PHYSICAL_KEY_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
  PHYSICAL_KEY_INTERNATIONAL2 = 136,
  PHYSICAL_KEY_INTERNATIONAL3 = 137, /**< Yen */
  PHYSICAL_KEY_INTERNATIONAL4 = 138,
  PHYSICAL_KEY_INTERNATIONAL5 = 139,
  PHYSICAL_KEY_INTERNATIONAL6 = 140,
  PHYSICAL_KEY_INTERNATIONAL7 = 141,
  PHYSICAL_KEY_INTERNATIONAL8 = 142,
  PHYSICAL_KEY_INTERNATIONAL9 = 143,
  PHYSICAL_KEY_LANG1 = 144, /**< Hangul/English toggle */
  PHYSICAL_KEY_LANG2 = 145, /**< Hanja conversion */
  PHYSICAL_KEY_LANG3 = 146, /**< Katakana */
  PHYSICAL_KEY_LANG4 = 147, /**< Hiragana */
  PHYSICAL_KEY_LANG5 = 148, /**< Zenkaku/Hankaku */
  PHYSICAL_KEY_LANG6 = 149, /**< reserved */
  PHYSICAL_KEY_LANG7 = 150, /**< reserved */
  PHYSICAL_KEY_LANG8 = 151, /**< reserved */
  PHYSICAL_KEY_LANG9 = 152, /**< reserved */

  PHYSICAL_KEY_ALTERASE = 153,    /**< Erase-Eaze */
  PHYSICAL_KEY_SYSREQ = 154,
  PHYSICAL_KEY_CANCEL = 155,      /**< AC Cancel */
  PHYSICAL_KEY_CLEAR = 156,
  PHYSICAL_KEY_PRIOR = 157,
  PHYSICAL_KEY_RETURN2 = 158,
  PHYSICAL_KEY_SEPARATOR = 159,
  PHYSICAL_KEY_OUT = 160,
  PHYSICAL_KEY_OPER = 161,
  PHYSICAL_KEY_CLEARAGAIN = 162,
  PHYSICAL_KEY_CRSEL = 163,
  PHYSICAL_KEY_EXSEL = 164,

  PHYSICAL_KEY_KP_00 = 176,
  PHYSICAL_KEY_KP_000 = 177,
  PHYSICAL_KEY_THOUSANDSSEPARATOR = 178,
  PHYSICAL_KEY_DECIMALSEPARATOR = 179,
  PHYSICAL_KEY_CURRENCYUNIT = 180,
  PHYSICAL_KEY_CURRENCYSUBUNIT = 181,
  PHYSICAL_KEY_KP_LEFTPAREN = 182,
  PHYSICAL_KEY_KP_RIGHTPAREN = 183,
  PHYSICAL_KEY_KP_LEFTBRACE = 184,
  PHYSICAL_KEY_KP_RIGHTBRACE = 185,
  PHYSICAL_KEY_KP_TAB = 186,
  PHYSICAL_KEY_KP_BACKSPACE = 187,
  PHYSICAL_KEY_KP_A = 188,
  PHYSICAL_KEY_KP_B = 189,
  PHYSICAL_KEY_KP_C = 190,
  PHYSICAL_KEY_KP_D = 191,
  PHYSICAL_KEY_KP_E = 192,
  PHYSICAL_KEY_KP_F = 193,
  PHYSICAL_KEY_KP_XOR = 194,
  PHYSICAL_KEY_KP_POWER = 195,
  PHYSICAL_KEY_KP_PERCENT = 196,
  PHYSICAL_KEY_KP_LESS = 197,
  PHYSICAL_KEY_KP_GREATER = 198,
  PHYSICAL_KEY_KP_AMPERSAND = 199,
  PHYSICAL_KEY_KP_DBLAMPERSAND = 200,
  PHYSICAL_KEY_KP_VERTICALBAR = 201,
  PHYSICAL_KEY_KP_DBLVERTICALBAR = 202,
  PHYSICAL_KEY_KP_COLON = 203,
  PHYSICAL_KEY_KP_HASH = 204,
  PHYSICAL_KEY_KP_SPACE = 205,
  PHYSICAL_KEY_KP_AT = 206,
  PHYSICAL_KEY_KP_EXCLAM = 207,
  PHYSICAL_KEY_KP_MEMSTORE = 208,
  PHYSICAL_KEY_KP_MEMRECALL = 209,
  PHYSICAL_KEY_KP_MEMCLEAR = 210,
  PHYSICAL_KEY_KP_MEMADD = 211,
  PHYSICAL_KEY_KP_MEMSUBTRACT = 212,
  PHYSICAL_KEY_KP_MEMMULTIPLY = 213,
  PHYSICAL_KEY_KP_MEMDIVIDE = 214,
  PHYSICAL_KEY_KP_PLUSMINUS = 215,
  PHYSICAL_KEY_KP_CLEAR = 216,
  PHYSICAL_KEY_KP_CLEARENTRY = 217,
  PHYSICAL_KEY_KP_BINARY = 218,
  PHYSICAL_KEY_KP_OCTAL = 219,
  PHYSICAL_KEY_KP_DECIMAL = 220,
  PHYSICAL_KEY_KP_HEXADECIMAL = 221,

  PHYSICAL_KEY_LCTRL = 224,
  PHYSICAL_KEY_LSHIFT = 225,
  PHYSICAL_KEY_LALT = 226, /**< alt, option */
  PHYSICAL_KEY_LGUI = 227, /**< windows, command (apple), meta */
  PHYSICAL_KEY_RCTRL = 228,
  PHYSICAL_KEY_RSHIFT = 229,
  PHYSICAL_KEY_RALT = 230, /**< alt gr, option */
  PHYSICAL_KEY_RGUI = 231, /**< windows, command (apple), meta */

  PHYSICAL_KEY_MODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special KMOD_MODE for it I'm adding it here
                                 */

  /* @} *//* Usage page 0x07 */

  /**
   *  \name Usage page 0x0C
   *
   *  These values are mapped from usage page 0x0C (USB consumer page).
   *  See https://usb.org/sites/default/files/hut1_2.pdf
   *
   *  There are way more keys in the spec than we can represent in the
   *  current scancode range, so pick the ones that commonly come up in
   *  real world usage.
   */
  /* @{ */

  PHYSICAL_KEY_AUDIONEXT = 258,
  PHYSICAL_KEY_AUDIOPREV = 259,
  PHYSICAL_KEY_AUDIOSTOP = 260,
  PHYSICAL_KEY_AUDIOPLAY = 261,
  PHYSICAL_KEY_AUDIOMUTE = 262,
  PHYSICAL_KEY_MEDIASELECT = 263,
  PHYSICAL_KEY_WWW = 264,             /**< AL Internet Browser */
  PHYSICAL_KEY_MAIL = 265,
  PHYSICAL_KEY_CALCULATOR = 266,      /**< AL Calculator */
  PHYSICAL_KEY_COMPUTER = 267,
  PHYSICAL_KEY_AC_SEARCH = 268,       /**< AC Search */
  PHYSICAL_KEY_AC_HOME = 269,         /**< AC Home */
  PHYSICAL_KEY_AC_BACK = 270,         /**< AC Back */
  PHYSICAL_KEY_AC_FORWARD = 271,      /**< AC Forward */
  PHYSICAL_KEY_AC_STOP = 272,         /**< AC Stop */
  PHYSICAL_KEY_AC_REFRESH = 273,      /**< AC Refresh */
  PHYSICAL_KEY_AC_BOOKMARKS = 274,    /**< AC Bookmarks */

  /* @} *//* Usage page 0x0C */

  /**
   *  \name Walther keys
   *
   *  These are values that Christian Walther added (for mac keyboard?).
   */
  /* @{ */

  PHYSICAL_KEY_BRIGHTNESSDOWN = 275,
  PHYSICAL_KEY_BRIGHTNESSUP = 276,
  PHYSICAL_KEY_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                           switch, video mode switch */
  PHYSICAL_KEY_KBDILLUMTOGGLE = 278,
  PHYSICAL_KEY_KBDILLUMDOWN = 279,
  PHYSICAL_KEY_KBDILLUMUP = 280,
  PHYSICAL_KEY_EJECT = 281,
  PHYSICAL_KEY_SLEEP = 282,           /**< SC System Sleep */

  PHYSICAL_KEY_APP1 = 283,
  PHYSICAL_KEY_APP2 = 284,

  /* @} *//* Walther keys */

  /**
   *  \name Usage page 0x0C (additional media keys)
   *
   *  These values are mapped from usage page 0x0C (USB consumer page).
   */
  /* @{ */

  PHYSICAL_KEY_AUDIOREWIND = 285,
  PHYSICAL_KEY_AUDIOFASTFORWARD = 286,

  /* @} *//* Usage page 0x0C (additional media keys) */

  /**
   *  \name Mobile keys
   *
   *  These are values that are often used on mobile phones.
   */
  /* @{ */

  PHYSICAL_KEY_SOFTLEFT = 287, /**< Usually situated below the display on phones and
                                      used as a multi-function feature key for selecting
                                      a software defined function shown on the bottom left
                                      of the display. */
  PHYSICAL_KEY_SOFTRIGHT = 288, /**< Usually situated below the display on phones and
                                       used as a multi-function feature key for selecting
                                       a software defined function shown on the bottom right
                                       of the display. */
  PHYSICAL_KEY_CALL = 289, /**< Used for accepting phone calls. */
  PHYSICAL_KEY_ENDCALL = 290, /**< Used for rejecting phone calls. */
} PhysicalKey;

#endif //TOYBOX_SRC_INTPUS_KEYCODE_H_
