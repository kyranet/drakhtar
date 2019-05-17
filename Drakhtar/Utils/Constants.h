// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <string>
#include <SDL_scancode.h>

// Window dimensions
const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;
const int ANIMATION_TICKS_PER_SECOND = 1;
const int GAME_FRAMERATE = 60;

/*
 * \brief This is displaying all the stats each unit has.
 * \Speed is capped at 10, meaning 10 is the max amount of speed one unit can
 have
 * \ataque		10
        defensa		10
        Maxhp			10
        attackrange	1
        moverange	3
        speed		4
        Base price	20
 * \Mage: Squishy glass cannon that deals good damage but dies very fast
   \Knight: Quick unit to burst through ranged units, fails to kill melee units
    fast
   \Archer: Longest ranged unit, attacks to up to 3 cells of distance, can
    kite golems well \Monster: A tank that hits hard if you step into his
    zone,defends key zones very well
   \Soldier: A little good in everything, can serve for various purposes
 */
struct UnitStats {
  uint16_t attack;
  uint16_t defense;
  uint16_t maxHealth;
  uint16_t attackRange;
  uint16_t moveRange;
  uint16_t speed;
  uint16_t prize;
};
struct TutorialTexts {
  std::string dialogtexts_;
  bool next_;
};

// Thassa
const UnitStats THASSA_STATS = {35, 35, 150, 1, 3, 5, 200};
// Zamdran
const UnitStats ZAMDRAN_STATS = {50, 10, 200, 3, 2, 5, 200};
// Sheissah
const UnitStats SHEISSAH_STATS = {60, 10, 220, 2, 2, 5, 200};
// Valar
const UnitStats VALAR_STATS = {35, 35, 150, 1, 3, 5, 200};
// Dreilay
const UnitStats DREILAY_STATS = {50, 35, 300, 1, 5, 8, 200};
// Abeizul
const UnitStats ABEIZHUL_STATS = {50, 20, 400, 3, 3, 6, 200};

// Mage
const UnitStats MAGE_STATS = {15, 0, 10, 2, 3, 6, 38 / 2};
// knight
const UnitStats KNIGHT_STATS = {13, 30, 30, 1, 5, 8, 55 / 2};
// archer
const UnitStats ARCHER_STATS = {6, 10, 9, 3, 2, 4, 26 / 2};
// soldier
const UnitStats SOLDIER_STATS = {8, 25, 12, 1, 3, 5, 28 / 2};
// monster
const UnitStats MONSTER_STATS = {19, 50, 85, 1, 2, 3, 125 / 2};

enum class KeyboardKey {
  UNKNOWN = SDL_SCANCODE_UNKNOWN,
  RESERVED1 = 1,
  RESERVED2 = 2,
  RESERVED3 = 3,
  A = SDL_SCANCODE_A,
  B = SDL_SCANCODE_B,
  C = SDL_SCANCODE_C,
  D = SDL_SCANCODE_D,
  E = SDL_SCANCODE_E,
  F = SDL_SCANCODE_F,
  G = SDL_SCANCODE_G,
  H = SDL_SCANCODE_H,
  I = SDL_SCANCODE_I,
  J = SDL_SCANCODE_J,
  K = SDL_SCANCODE_K,
  L = SDL_SCANCODE_L,
  M = SDL_SCANCODE_M,
  N = SDL_SCANCODE_N,
  O = SDL_SCANCODE_O,
  P = SDL_SCANCODE_P,
  Q = SDL_SCANCODE_Q,
  R = SDL_SCANCODE_R,
  S = SDL_SCANCODE_S,
  T = SDL_SCANCODE_T,
  U = SDL_SCANCODE_U,
  V = SDL_SCANCODE_V,
  W = SDL_SCANCODE_W,
  X = SDL_SCANCODE_X,
  Y = SDL_SCANCODE_Y,
  Z = SDL_SCANCODE_Z,

  NUM_1 = SDL_SCANCODE_1,
  NUM_2 = SDL_SCANCODE_2,
  NUM_3 = SDL_SCANCODE_3,
  NUM_4 = SDL_SCANCODE_4,
  NUM_5 = SDL_SCANCODE_5,
  NUM_6 = SDL_SCANCODE_6,
  NUM_7 = SDL_SCANCODE_7,
  NUM_8 = SDL_SCANCODE_8,
  NUM_9 = SDL_SCANCODE_9,
  NUM_0 = SDL_SCANCODE_0,

  RETURN = SDL_SCANCODE_RETURN,
  ESCAPE = SDL_SCANCODE_ESCAPE,
  BACKSPACE = SDL_SCANCODE_BACKSPACE,
  TAB = SDL_SCANCODE_TAB,
  SPACE = SDL_SCANCODE_SPACE,

  MINUS = SDL_SCANCODE_MINUS,
  EQUALS = SDL_SCANCODE_EQUALS,
  LEFT_BRACKET = SDL_SCANCODE_LEFTBRACKET,
  RIGHT_BRACKET = SDL_SCANCODE_RIGHTBRACKET,
  BACKSLASH = SDL_SCANCODE_BACKSLASH,
  NO_NUS_HASH = SDL_SCANCODE_NONUSHASH,
  SEMICOLON = SDL_SCANCODE_SEMICOLON,
  APOSTROPHE = SDL_SCANCODE_APOSTROPHE,
  GRAVE = SDL_SCANCODE_GRAVE,
  COMMA = SDL_SCANCODE_COMMA,
  PERIOD = SDL_SCANCODE_PERIOD,
  SLASH = SDL_SCANCODE_SLASH,

  CAPS_LOCK = SDL_SCANCODE_CAPSLOCK,

  F1 = SDL_SCANCODE_F1,
  F2 = SDL_SCANCODE_F2,
  F3 = SDL_SCANCODE_F3,
  F4 = SDL_SCANCODE_F4,
  F5 = SDL_SCANCODE_F5,
  F6 = SDL_SCANCODE_F6,
  F7 = SDL_SCANCODE_F7,
  F8 = SDL_SCANCODE_F8,
  F9 = SDL_SCANCODE_F9,
  F10 = SDL_SCANCODE_F10,
  F11 = SDL_SCANCODE_F11,
  F12 = SDL_SCANCODE_F12,

  PRINT_SCREEN = SDL_SCANCODE_PRINTSCREEN,
  SCROLL_LOCK = SDL_SCANCODE_SCROLLLOCK,
  PAUSE = SDL_SCANCODE_PAUSE,
  INSERT = SDL_SCANCODE_INSERT,
  HOME = SDL_SCANCODE_HOME,
  PAGEUP = SDL_SCANCODE_PAGEUP,
  DELETE = SDL_SCANCODE_DELETE,
  END = SDL_SCANCODE_END,
  PAGEDOWN = SDL_SCANCODE_PAGEDOWN,
  RIGHT = SDL_SCANCODE_RIGHT,
  LEFT = SDL_SCANCODE_LEFT,
  DOWN = SDL_SCANCODE_DOWN,
  UP = SDL_SCANCODE_UP,

  NUM_LOCK_CLEAR = SDL_SCANCODE_NUMLOCKCLEAR,
  KEYPAD_DIVIDE = SDL_SCANCODE_KP_DIVIDE,
  KEYPAD_MULTIPLY = SDL_SCANCODE_KP_MULTIPLY,
  KEYPAD_MINUS = SDL_SCANCODE_KP_MINUS,
  KEYPAD_PLUS = SDL_SCANCODE_KP_PLUS,
  KEYPAD_ENTER = SDL_SCANCODE_KP_ENTER,
  KEYPAD_1 = SDL_SCANCODE_KP_1,
  KEYPAD_2 = SDL_SCANCODE_KP_2,
  KEYPAD_3 = SDL_SCANCODE_KP_3,
  KEYPAD_4 = SDL_SCANCODE_KP_4,
  KEYPAD_5 = SDL_SCANCODE_KP_5,
  KEYPAD_6 = SDL_SCANCODE_KP_6,
  KEYPAD_7 = SDL_SCANCODE_KP_7,
  KEYPAD_8 = SDL_SCANCODE_KP_8,
  KEYPAD_9 = SDL_SCANCODE_KP_9,
  KEYPAD_0 = SDL_SCANCODE_KP_0,
  KEYPAD_PERIOD = SDL_SCANCODE_KP_PERIOD,

  NO_NUS_BACKSLASH = SDL_SCANCODE_NONUSBACKSLASH,
  APPLICATION = SDL_SCANCODE_APPLICATION,
  POWER = SDL_SCANCODE_POWER,
  KEYPAD_EQUALS = SDL_SCANCODE_KP_EQUALS,
  F13 = SDL_SCANCODE_F13,
  F14 = SDL_SCANCODE_F14,
  F15 = SDL_SCANCODE_F15,
  F16 = SDL_SCANCODE_F16,
  F17 = SDL_SCANCODE_F17,
  F18 = SDL_SCANCODE_F18,
  F19 = SDL_SCANCODE_F19,
  F20 = SDL_SCANCODE_F20,
  F21 = SDL_SCANCODE_F21,
  F22 = SDL_SCANCODE_F22,
  F23 = SDL_SCANCODE_F23,
  F24 = SDL_SCANCODE_F24,
  EXECUTE = SDL_SCANCODE_EXECUTE,
  HELP = SDL_SCANCODE_HELP,
  MENU = SDL_SCANCODE_MENU,
  SELECT = SDL_SCANCODE_SELECT,
  STOP = SDL_SCANCODE_STOP,
  AGAIN = SDL_SCANCODE_AGAIN,
  UNDO = SDL_SCANCODE_UNDO,
  CUT = SDL_SCANCODE_CUT,
  COPY = SDL_SCANCODE_COPY,
  PASTE = SDL_SCANCODE_PASTE,
  FIND = SDL_SCANCODE_FIND,
  MUTE = SDL_SCANCODE_MUTE,
  VOLUME_UP = SDL_SCANCODE_VOLUMEUP,
  VOLUME_DOWN = SDL_SCANCODE_VOLUMEDOWN,
  LOCKING_CAPS_LOCK = 130,
  LOCKING_NUM_LOCK = 131,
  LOCKING_SCROLL_LOCK = 132,
  KEYPAD_COMMA = SDL_SCANCODE_KP_COMMA,
  KEYPAD_EQUAL_SAS400 = SDL_SCANCODE_KP_EQUALSAS400,

  INTERNATIONAL1 = SDL_SCANCODE_INTERNATIONAL1,
  INTERNATIONAL2 = SDL_SCANCODE_INTERNATIONAL2,
  INTERNATIONAL3 = SDL_SCANCODE_INTERNATIONAL3,
  INTERNATIONAL4 = SDL_SCANCODE_INTERNATIONAL4,
  INTERNATIONAL5 = SDL_SCANCODE_INTERNATIONAL5,
  INTERNATIONAL6 = SDL_SCANCODE_INTERNATIONAL6,
  INTERNATIONAL7 = SDL_SCANCODE_INTERNATIONAL7,
  INTERNATIONAL8 = SDL_SCANCODE_INTERNATIONAL8,
  INTERNATIONAL9 = SDL_SCANCODE_INTERNATIONAL9,
  LANG1 = SDL_SCANCODE_LANG1,
  LANG2 = SDL_SCANCODE_LANG2,
  LANG3 = SDL_SCANCODE_LANG3,
  LANG4 = SDL_SCANCODE_LANG4,
  LANG5 = SDL_SCANCODE_LANG5,
  LANG6 = SDL_SCANCODE_LANG6,
  LANG7 = SDL_SCANCODE_LANG7,
  LANG8 = SDL_SCANCODE_LANG8,
  LANG9 = SDL_SCANCODE_LANG9,

  ALTERASE = SDL_SCANCODE_ALTERASE,
  SYSREQ = SDL_SCANCODE_SYSREQ,
  CANCEL = SDL_SCANCODE_CANCEL,
  CLEAR = SDL_SCANCODE_CLEAR,
  PRIOR = SDL_SCANCODE_PRIOR,
  RETURN2 = SDL_SCANCODE_RETURN2,
  SEPARATOR = SDL_SCANCODE_SEPARATOR,
  OUT = SDL_SCANCODE_OUT,
  OPER = SDL_SCANCODE_OPER,
  CLEAR_AGAIN = SDL_SCANCODE_CLEARAGAIN,
  CRSEL = SDL_SCANCODE_CRSEL,
  EXSEL = SDL_SCANCODE_EXSEL,

  KEYPAD_00 = SDL_SCANCODE_KP_00,
  KEYPAD_000 = SDL_SCANCODE_KP_000,
  THOUSANDS_SEPARATOR = SDL_SCANCODE_THOUSANDSSEPARATOR,
  DECIMAL_SEPARATOR = SDL_SCANCODE_DECIMALSEPARATOR,
  CURRENCY_UNIT = SDL_SCANCODE_CURRENCYUNIT,
  CURRENCY_SUBUNIT = SDL_SCANCODE_CURRENCYSUBUNIT,
  KEYPAD_LEFT_PAREN = SDL_SCANCODE_KP_LEFTPAREN,
  KEYPAD_RIGHT_PAREN = SDL_SCANCODE_KP_RIGHTPAREN,
  KEYPAD_LEFT_BRACE = SDL_SCANCODE_KP_LEFTBRACE,
  KEYPAD_RIGHT_BRACE = SDL_SCANCODE_KP_RIGHTBRACE,
  KEYPAD_TAB = SDL_SCANCODE_KP_TAB,
  KEYPAD_BACKSPACE = SDL_SCANCODE_KP_BACKSPACE,
  KEYPAD_A = SDL_SCANCODE_KP_A,
  KEYPAD_B = SDL_SCANCODE_KP_B,
  KEYPAD_C = SDL_SCANCODE_KP_C,
  KEYPAD_D = SDL_SCANCODE_KP_D,
  KEYPAD_E = SDL_SCANCODE_KP_E,
  KEYPAD_F = SDL_SCANCODE_KP_F,
  KEYPAD_XOR = SDL_SCANCODE_KP_XOR,
  KEYPAD_POWER = SDL_SCANCODE_KP_POWER,
  KEYPAD_PERCENT = SDL_SCANCODE_KP_PERCENT,
  KEYPAD_LESS = SDL_SCANCODE_KP_LESS,
  KEYPAD_GREATER = SDL_SCANCODE_KP_GREATER,
  KEYPAD_AMPERSAND = SDL_SCANCODE_KP_AMPERSAND,
  KEYPAD_DBLAMPERSAND = SDL_SCANCODE_KP_DBLAMPERSAND,
  KEYPAD_VERTICALBAR = SDL_SCANCODE_KP_VERTICALBAR,
  KEYPAD_DBLVERTICALBAR = SDL_SCANCODE_KP_DBLVERTICALBAR,
  KEYPAD_COLON = SDL_SCANCODE_KP_COLON,
  KEYPAD_HASH = SDL_SCANCODE_KP_HASH,
  KEYPAD_SPACE = SDL_SCANCODE_KP_SPACE,
  KEYPAD_AT = SDL_SCANCODE_KP_AT,
  KEYPAD_EXCLAM = SDL_SCANCODE_KP_EXCLAM,
  KEYPAD_MEMSTORE = SDL_SCANCODE_KP_MEMSTORE,
  KEYPAD_MEMRECALL = SDL_SCANCODE_KP_MEMRECALL,
  KEYPAD_MEMCLEAR = SDL_SCANCODE_KP_MEMCLEAR,
  KEYPAD_MEMADD = SDL_SCANCODE_KP_MEMADD,
  KEYPAD_MEMSUBTRACT = SDL_SCANCODE_KP_MEMSUBTRACT,
  KEYPAD_MEMMULTIPLY = SDL_SCANCODE_KP_MEMMULTIPLY,
  KEYPAD_MEMDIVIDE = SDL_SCANCODE_KP_MEMDIVIDE,
  KEYPAD_PLUSMINUS = SDL_SCANCODE_KP_PLUSMINUS,
  KEYPAD_CLEAR = SDL_SCANCODE_KP_CLEAR,
  KEYPAD_CLEARENTRY = SDL_SCANCODE_KP_CLEARENTRY,
  KEYPAD_BINARY = SDL_SCANCODE_KP_BINARY,
  KEYPAD_OCTAL = SDL_SCANCODE_KP_OCTAL,
  KEYPAD_DECIMAL = SDL_SCANCODE_KP_DECIMAL,
  KEYPAD_HEXADECIMAL = SDL_SCANCODE_KP_HEXADECIMAL,

  LEFT_CTRL = SDL_SCANCODE_LCTRL,
  LEFT_SHIFT = SDL_SCANCODE_LSHIFT,
  LEFT_ALT = SDL_SCANCODE_LALT,
  LEFT_GUI = SDL_SCANCODE_LGUI,
  RIGHT_CTRL = SDL_SCANCODE_RCTRL,
  RIGHT_SHIFT = SDL_SCANCODE_RSHIFT,
  RIGHT_ALT = SDL_SCANCODE_RALT,
  RIGHT_GUI = SDL_SCANCODE_RGUI,
  MODE = SDL_SCANCODE_MODE,

  AUDIONEXT = SDL_SCANCODE_AUDIONEXT,
  AUDIOPREV = SDL_SCANCODE_AUDIOPREV,
  AUDIOSTOP = SDL_SCANCODE_AUDIOSTOP,
  AUDIOPLAY = SDL_SCANCODE_AUDIOPLAY,
  AUDIOMUTE = SDL_SCANCODE_AUDIOMUTE,
  MEDIASELECT = SDL_SCANCODE_MEDIASELECT,
  WWW = SDL_SCANCODE_WWW,
  MAIL = SDL_SCANCODE_MAIL,
  CALCULATOR = SDL_SCANCODE_CALCULATOR,
  COMPUTER = SDL_SCANCODE_COMPUTER,
  AC_SEARCH = SDL_SCANCODE_AC_SEARCH,
  AC_HOME = SDL_SCANCODE_AC_HOME,
  AC_BACK = SDL_SCANCODE_AC_BACK,
  AC_FORWARD = SDL_SCANCODE_AC_FORWARD,
  AC_STOP = SDL_SCANCODE_AC_STOP,
  AC_REFRESH = SDL_SCANCODE_AC_REFRESH,
  AC_BOOKMARKS = SDL_SCANCODE_AC_BOOKMARKS,

  BRIGHTNESS_DOWN = SDL_SCANCODE_BRIGHTNESSDOWN,
  BRIGHTNESS_UP = SDL_SCANCODE_BRIGHTNESSUP,
  DISPLAY_SWITCH = SDL_SCANCODE_DISPLAYSWITCH,

  KBDILLUMTOGGLE = SDL_SCANCODE_KBDILLUMTOGGLE,
  KBDILLUMDOWN = SDL_SCANCODE_KBDILLUMDOWN,
  KBDILLUMUP = SDL_SCANCODE_KBDILLUMUP,
  EJECT = SDL_SCANCODE_EJECT,
  SLEEP = SDL_SCANCODE_SLEEP,

  kKeyLimit
};

enum class MouseKey { LEFT, MIDDLE, RIGHT, kKeyLimit };
