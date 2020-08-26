#pragma once

// From glfw3.h

/* Printable keys */
enum class PrintableKeys
{
  EN_KEY_SPACE             = 32,
  EN_KEY_APOSTROPHE        = 39,  /* ' */
  EN_KEY_COMMA             = 44,  /* , */
  EN_KEY_MINUS             = 45,  /* - */
  EN_KEY_PERIOD            = 46,  /* . */
  EN_KEY_SLASH             = 47,  /* / */
  EN_KEY_0                 = 48,
  EN_KEY_1                 = 49,
  EN_KEY_2                 = 50,
  EN_KEY_3                 = 51,
  EN_KEY_4                 = 52,
  EN_KEY_5                 = 53,
  EN_KEY_6                 = 54,
  EN_KEY_7                 = 55,
  EN_KEY_8                 = 56,
  EN_KEY_9                 = 57,
  EN_KEY_SEMICOLON         = 59,  /* ; */
  EN_KEY_EQUAL             = 61,  /* = */
  EN_KEY_A                 = 65,
  EN_KEY_B                 = 66,
  EN_KEY_C                 = 67,
  EN_KEY_D                 = 68,
  EN_KEY_E                 = 69,
  EN_KEY_F                 = 70,
  EN_KEY_G                 = 71,
  EN_KEY_H                 = 72,
  EN_KEY_I                 = 73,
  EN_KEY_J                 = 74,
  EN_KEY_K                 = 75,
  EN_KEY_L                 = 76,
  EN_KEY_M                 = 77,
  EN_KEY_N                 = 78,
  EN_KEY_O                 = 79,
  EN_KEY_P                 = 80,
  EN_KEY_Q                 = 81,
  EN_KEY_R                 = 82,
  EN_KEY_S                 = 83,
  EN_KEY_T                 = 84,
  EN_KEY_U                 = 85,
  EN_KEY_V                 = 86,
  EN_KEY_W                 = 87,
  EN_KEY_X                 = 88,
  EN_KEY_Y                 = 89,
  EN_KEY_Z                 = 90,
  EN_KEY_LEFT_BRACKET      = 91,  /* [ */
  EN_KEY_BACKSLASH         = 92,  /* \ */
  EN_KEY_RIGHT_BRACKET     = 93,  /* ] */
  EN_KEY_GRAVE_ACCENT      = 96,  /* ` */
  EN_KEY_WORLD_1           = 161, /* non-US #1 */
  EN_KEY_WORLD_2           = 162 /* non-US #2 */
};
//#define EN_KEY_SPACE              32
//#define EN_KEY_APOSTROPHE         39  /* ' */
//#define EN_KEY_COMMA              44  /* , */
//#define EN_KEY_MINUS              45  /* - */
//#define EN_KEY_PERIOD             46  /* . */
//#define EN_KEY_SLASH              47  /* / */
//#define EN_KEY_0                  48
//#define EN_KEY_1                  49
//#define EN_KEY_2                  50
//#define EN_KEY_3                  51
//#define EN_KEY_4                  52
//#define EN_KEY_5                  53
//#define EN_KEY_6                  54
//#define EN_KEY_7                  55
//#define EN_KEY_8                  56
//#define EN_KEY_9                  57
//#define EN_KEY_SEMICOLON          59  /* ; */
//#define EN_KEY_EQUAL              61  /* = */
//#define EN_KEY_A                  65
//#define EN_KEY_B                  66
//#define EN_KEY_C                  67
//#define EN_KEY_D                  68
//#define EN_KEY_E                  69
//#define EN_KEY_F                  70
//#define EN_KEY_G                  71
//#define EN_KEY_H                  72
//#define EN_KEY_I                  73
//#define EN_KEY_J                  74
//#define EN_KEY_K                  75
//#define EN_KEY_L                  76
//#define EN_KEY_M                  77
//#define EN_KEY_N                  78
//#define EN_KEY_O                  79
//#define EN_KEY_P                  80
//#define EN_KEY_Q                  81
//#define EN_KEY_R                  82
//#define EN_KEY_S                  83
//#define EN_KEY_T                  84
//#define EN_KEY_U                  85
//#define EN_KEY_V                  86
//#define EN_KEY_W                  87
//#define EN_KEY_X                  88
//#define EN_KEY_Y                  89
//#define EN_KEY_Z                  90
//#define EN_KEY_LEFT_BRACKET       91  /* [ */
//#define EN_KEY_BACKSLASH          92  /* \ */
//#define EN_KEY_RIGHT_BRACKET      93  /* ] */
//#define EN_KEY_GRAVE_ACCENT       96  /* ` */
//#define EN_KEY_WORLD_1            161 /* non-US #1 */
//#define EN_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
enum class FunctionKeys
{
  EN_KEY_ESCAPE            = 256,
  EN_KEY_ENTER             = 257,
  EN_KEY_TAB               = 258,
  EN_KEY_BACKSPACE         = 259,
  EN_KEY_INSERT            = 260,
  EN_KEY_DELETE            = 261,
  EN_KEY_RIGHT             = 262,
  EN_KEY_LEFT              = 263,
  EN_KEY_DOWN              = 264,
  EN_KEY_UP                = 265,
  EN_KEY_PAGE_UP           = 266,
  EN_KEY_PAGE_DOWN         = 267,
  EN_KEY_HOME              = 268,
  EN_KEY_END               = 269,
  EN_KEY_CAPS_LOCK         = 280,
  EN_KEY_SCROLL_LOCK       = 281,
  EN_KEY_NUM_LOCK          = 282,
  EN_KEY_PRINT_SCREEN      = 283,
  EN_KEY_PAUSE             = 284,
  EN_KEY_F1                = 290,
  EN_KEY_F2                = 291,
  EN_KEY_F3                = 292,
  EN_KEY_F4                = 293,
  EN_KEY_F5                = 294,
  EN_KEY_F6                = 295,
  EN_KEY_F7                = 296,
  EN_KEY_F8                = 297,
  EN_KEY_F9                = 298,
  EN_KEY_F10               = 299,
  EN_KEY_F11               = 300,
  EN_KEY_F12               = 301,
  EN_KEY_F13               = 302,
  EN_KEY_F14               = 303,
  EN_KEY_F15               = 304,
  EN_KEY_F16               = 305,
  EN_KEY_F17               = 306,
  EN_KEY_F18               = 307,
  EN_KEY_F19               = 308,
  EN_KEY_F20               = 309,
  EN_KEY_F21               = 310,
  EN_KEY_F22               = 311,
  EN_KEY_F23               = 312,
  EN_KEY_F24               = 313,
  EN_KEY_F25               = 314,
  EN_KEY_KP_0              = 320,
  EN_KEY_KP_1              = 321,
  EN_KEY_KP_2              = 322,
  EN_KEY_KP_3              = 323,
  EN_KEY_KP_4              = 324,
  EN_KEY_KP_5              = 325,
  EN_KEY_KP_6              = 326,
  EN_KEY_KP_7              = 327,
  EN_KEY_KP_8              = 328,
  EN_KEY_KP_9              = 329,
  EN_KEY_KP_DECIMAL        = 330,
  EN_KEY_KP_DIVIDE         = 331,
  EN_KEY_KP_MULTIPLY       = 332,
  EN_KEY_KP_SUBTRACT       = 333,
  EN_KEY_KP_ADD            = 334,
  EN_KEY_KP_ENTER          = 335,
  EN_KEY_KP_EQUAL          = 336,
  EN_KEY_LEFT_SHIFT        = 340,
  EN_KEY_LEFT_CONTROL      = 341,
  EN_KEY_LEFT_ALT          = 342,
  EN_KEY_LEFT_SUPER        = 343,
  EN_KEY_RIGHT_SHIFT       = 344,
  EN_KEY_RIGHT_CONTROL     = 345,
  EN_KEY_RIGHT_ALT         = 346,
  EN_KEY_RIGHT_SUPER       = 347,
  EN_KEY_MENU              = 348
};
//#define EN_KEY_ESCAPE             256
//#define EN_KEY_ENTER              257
//#define EN_KEY_TAB                258
//#define EN_KEY_BACKSPACE          259
//#define EN_KEY_INSERT             260
//#define EN_KEY_DELETE             261
//#define EN_KEY_RIGHT              262
//#define EN_KEY_LEFT               263
//#define EN_KEY_DOWN               264
//#define EN_KEY_UP                 265
//#define EN_KEY_PAGE_UP            266
//#define EN_KEY_PAGE_DOWN          267
//#define EN_KEY_HOME               268
//#define EN_KEY_END                269
//#define EN_KEY_CAPS_LOCK          280
//#define EN_KEY_SCROLL_LOCK        281
//#define EN_KEY_NUM_LOCK           282
//#define EN_KEY_PRINT_SCREEN       283
//#define EN_KEY_PAUSE              284
//#define EN_KEY_F1                 290
//#define EN_KEY_F2                 291
//#define EN_KEY_F3                 292
//#define EN_KEY_F4                 293
//#define EN_KEY_F5                 294
//#define EN_KEY_F6                 295
//#define EN_KEY_F7                 296
//#define EN_KEY_F8                 297
//#define EN_KEY_F9                 298
//#define EN_KEY_F10                299
//#define EN_KEY_F11                300
//#define EN_KEY_F12                301
//#define EN_KEY_F13                302
//#define EN_KEY_F14                303
//#define EN_KEY_F15                304
//#define EN_KEY_F16                305
//#define EN_KEY_F17                306
//#define EN_KEY_F18                307
//#define EN_KEY_F19                308
//#define EN_KEY_F20                309
//#define EN_KEY_F21                310
//#define EN_KEY_F22                311
//#define EN_KEY_F23                312
//#define EN_KEY_F24                313
//#define EN_KEY_F25                314
//#define EN_KEY_KP_0               320
//#define EN_KEY_KP_1               321
//#define EN_KEY_KP_2               322
//#define EN_KEY_KP_3               323
//#define EN_KEY_KP_4               324
//#define EN_KEY_KP_5               325
//#define EN_KEY_KP_6               326
//#define EN_KEY_KP_7               327
//#define EN_KEY_KP_8               328
//#define EN_KEY_KP_9               329
//#define EN_KEY_KP_DECIMAL         330
//#define EN_KEY_KP_DIVIDE          331
//#define EN_KEY_KP_MULTIPLY        332
//#define EN_KEY_KP_SUBTRACT        333
//#define EN_KEY_KP_ADD             334
//#define EN_KEY_KP_ENTER           335
//#define EN_KEY_KP_EQUAL           336
//#define EN_KEY_LEFT_SHIFT         340
//#define EN_KEY_LEFT_CONTROL       341
//#define EN_KEY_LEFT_ALT           342
//#define EN_KEY_LEFT_SUPER         343
//#define EN_KEY_RIGHT_SHIFT        344
//#define EN_KEY_RIGHT_CONTROL      345
//#define EN_KEY_RIGHT_ALT          346
//#define EN_KEY_RIGHT_SUPER        347
//#define EN_KEY_MENU               348