eq = require("eq")

EQ_ITEM_SIZE_TINY   = 0
EQ_ITEM_SIZE_SMALL  = 1
EQ_ITEM_SIZE_MEDIUM = 2
EQ_ITEM_SIZE_LARGE  = 3
EQ_ITEM_SIZE_GIANT  = 4

EQ_TEXT_COLOR_BLACK       = 0
EQ_TEXT_COLOR_GRAY        = 1
EQ_TEXT_COLOR_GREEN       = 2
EQ_TEXT_COLOR_GRAY2       = 3
EQ_TEXT_COLOR_BLUE        = 4
EQ_TEXT_COLOR_PINK        = 5
EQ_TEXT_COLOR_GRAY3       = 6
EQ_TEXT_COLOR_WHITE       = 7
EQ_TEXT_COLOR_GRAY4       = 8
EQ_TEXT_COLOR_GRAY5       = 9
EQ_TEXT_COLOR_WHITE2      = 10
EQ_TEXT_COLOR_GRAY6       = 11
EQ_TEXT_COLOR_LIGHT_GRAY  = 12
EQ_TEXT_COLOR_RED         = 13
EQ_TEXT_COLOR_LIGHT_GREEN = 14
EQ_TEXT_COLOR_YELLOW      = 15
EQ_TEXT_COLOR_LIGHT_BLUE  = 16
EQ_TEXT_COLOR_GRAY7       = 17
EQ_TEXT_COLOR_CYAN        = 18
EQ_TEXT_COLOR_GRAY8       = 19
EQ_TEXT_COLOR_BLACK2      = 20

EQ_KEY_NULL            = 0x00
EQ_KEY_ESCAPE          = 0x01
EQ_KEY_1               = 0x02
EQ_KEY_2               = 0x03
EQ_KEY_3               = 0x04
EQ_KEY_4               = 0x05
EQ_KEY_5               = 0x06
EQ_KEY_6               = 0x07
EQ_KEY_7               = 0x08
EQ_KEY_8               = 0x09
EQ_KEY_9               = 0x0A
EQ_KEY_0               = 0x0B
EQ_KEY_MINUS           = 0x0C
EQ_KEY_DASH            = EQ_KEY_MINUS
EQ_KEY_EQUALS          = 0x0D
EQ_KEY_BACK            = 0x0E
EQ_KEY_BACKSPACE       = EQ_KEY_BACK
EQ_KEY_TAB             = 0x0F
EQ_KEY_Q               = 0x10
EQ_KEY_W               = 0x11
EQ_KEY_E               = 0x12
EQ_KEY_R               = 0x13
EQ_KEY_T               = 0x14
EQ_KEY_Y               = 0x15
EQ_KEY_U               = 0x16
EQ_KEY_I               = 0x17
EQ_KEY_O               = 0x18
EQ_KEY_P               = 0x19
EQ_KEY_LBRACKET        = 0x1A
EQ_KEY_LEFT_BRACKET    = EQ_KEY_LBRACKET
EQ_KEY_RBRACKET        = 0x1B
EQ_KEY_RIGHT_BRACKET   = EQ_KEY_RBRACKET
EQ_KEY_RETURN          = 0x1C
EQ_KEY_ENTER           = EQ_KEY_RETURN
EQ_KEY_LCONTROL        = 0x1D
EQ_KEY_LEFT_CONTROL    = EQ_KEY_LCONTROL
EQ_KEY_A               = 0x1E
EQ_KEY_S               = 0x1F
EQ_KEY_D               = 0x20
EQ_KEY_F               = 0x21
EQ_KEY_G               = 0x22
EQ_KEY_H               = 0x23
EQ_KEY_J               = 0x24
EQ_KEY_K               = 0x25
EQ_KEY_L               = 0x26
EQ_KEY_SEMICOLON       = 0x27
EQ_KEY_APOSTROPHE      = 0x28
EQ_KEY_GRAVE           = 0x29
EQ_KEY_TILDE           = EQ_KEY_GRAVE
EQ_KEY_LSHIFT          = 0x2A
EQ_KEY_LEFT_SHIFT      = EQ_KEY_LSHIFT
EQ_KEY_BACKSLASH       = 0x2B
EQ_KEY_Z               = 0x2C
EQ_KEY_X               = 0x2D
EQ_KEY_C               = 0x2E
EQ_KEY_V               = 0x2F
EQ_KEY_B               = 0x30
EQ_KEY_N               = 0x31
EQ_KEY_M               = 0x32
EQ_KEY_COMMA           = 0x33
EQ_KEY_PERIOD          = 0x34
EQ_KEY_SLASH           = 0x35
EQ_KEY_RSHIFT          = 0x36
EQ_KEY_RIGHT_SHIFT     = EQ_KEY_RSHIFT
EQ_KEY_MULTIPLY        = 0x37
EQ_KEY_NUMPADSTAR      = EQ_KEY_NUMPAD_MULTIPLY
EQ_KEY_NUMPAD_MULTIPLY = EQ_KEY_NUMPAD_MULTIPLY
EQ_KEY_LMENU           = 0x38
EQ_KEY_LALT            = EQ_KEY_LMENU
EQ_KEY_LEFT_LALT       = EQ_KEY_LMENU
EQ_KEY_SPACE           = 0x39
EQ_KEY_SPACEBAR        = EQ_KEY_SPACE
EQ_KEY_CAPITAL         = 0x3A
EQ_KEY_CAPSLOCK        = EQ_KEY_CAPITAL
EQ_KEY_CAPS_LOCK       = EQ_KEY_CAPITAL
EQ_KEY_F1              = 0x3B
EQ_KEY_F2              = 0x3C
EQ_KEY_F3              = 0x3D
EQ_KEY_F4              = 0x3E
EQ_KEY_F5              = 0x3F
EQ_KEY_F6              = 0x40
EQ_KEY_F7              = 0x41
EQ_KEY_F8              = 0x42
EQ_KEY_F9              = 0x43
EQ_KEY_F10             = 0x44
EQ_KEY_NUMLOCK         = 0x45
EQ_KEY_NUM_LOCK        = EQ_KEY_NUMLOCK
EQ_KEY_SCROLL          = 0x46
EQ_KEY_SCROLL_LOCK     = EQ_KEY_SCROLL
EQ_KEY_NUMPAD7         = 0x47
EQ_KEY_NUMPAD8         = 0x48
EQ_KEY_NUMPAD9         = 0x49
EQ_KEY_SUBTRACT        = 0x4A
EQ_KEY_NUMPADMINUS     = EQ_KEY_SUBTRACT
EQ_KEY_NUMPAD_SUBTRACT = EQ_KEY_SUBTRACT
EQ_KEY_NUMPAD4         = 0x4B
EQ_KEY_NUMPAD5         = 0x4C
EQ_KEY_NUMPAD6         = 0x4D
EQ_KEY_ADD             = 0x4E
EQ_KEY_NUMPADPLUS      = 0x4E
EQ_KEY_NUMPAD_ADD      = 0x4E
EQ_KEY_NUMPAD1         = 0x4F
EQ_KEY_NUMPAD2         = 0x50
EQ_KEY_NUMPAD3         = 0x51
EQ_KEY_NUMPAD0         = 0x52
EQ_KEY_DECIMAL         = 0x53
EQ_KEY_NUMPADPERIOD    = EQ_KEY_DECIMAL
EQ_KEY_NUMPAD_PERIOD   = EQ_KEY_DECIMAL
EQ_KEY_OEM_102         = 0x56
EQ_KEY_F11             = 0x57
EQ_KEY_F12             = 0x58
EQ_KEY_F13             = 0x64
EQ_KEY_F14             = 0x65
EQ_KEY_F15             = 0x66
EQ_KEY_KANA            = 0x70
EQ_KEY_ABNT_C1         = 0x73
EQ_KEY_CONVERT         = 0x79
EQ_KEY_NOCONVERT       = 0x7B
EQ_KEY_NO_CONVERT      = EQ_KEY_NOCONVERT
EQ_KEY_YEN             = 0x7D
EQ_KEY_ABNT_C2         = 0x7E
EQ_KEY_NUMPADEQUALS    = 0x8D
EQ_KEY_NUMPAD_EQUALS   = EQ_KEY_NUMPADEQUALS
EQ_KEY_PREVTRACK       = 0x90
EQ_KEY_CIRCUMFLEX      = EQ_KEY_PREVTRACK
EQ_KEY_PREV_TRACK      = EQ_KEY_PREVTRACK
EQ_KEY_AT              = 0x91
EQ_KEY_COLON           = 0x92
EQ_KEY_UNDERLINE       = 0x93
EQ_KEY_KANJI           = 0x94
EQ_KEY_STOP            = 0x95
EQ_KEY_AX              = 0x96
EQ_KEY_UNLABELED       = 0x97
EQ_KEY_NEXTTRACK       = 0x99
EQ_KEY_NEXT_TRACK      = EQ_KEY_NEXTTRACK
EQ_KEY_NUMPADENTER     = 0x9C
EQ_KEY_NUMPAD_ENTER    = EQ_KEY_NUMPADENTER
EQ_KEY_RCONTROL        = 0x9D
EQ_KEY_RIGHT_CONTROL   = EQ_KEY_RCONTROL
EQ_KEY_MUTE            = 0xA0
EQ_KEY_CALCULATOR      = 0xA1
EQ_KEY_PLAYPAUSE       = 0xA2
EQ_KEY_PLAY_PAUSE      = EQ_KEY_PLAYPAUSE
EQ_KEY_MEDIASTOP       = 0xA4
EQ_KEY_MEDIA_STOP      = EQ_KEY_MEDIASTOP
EQ_KEY_VOLUMEDOWN      = 0xAE
EQ_KEY_VOLUME_DOWN     = EQ_KEY_VOLUMEDOWN
EQ_KEY_VOLUMEUP        = 0xB0
EQ_KEY_VOLUME_UP       = EQ_KEY_VOLUMEUP
EQ_KEY_WEBHOME         = 0xB2
EQ_KEY_WEB_HOME        = EQ_KEY_WEBHOME
EQ_KEY_NUMPADCOMMA     = 0xB3
EQ_KEY_NUMPAD_COMMA    = EQ_KEY_NUMPADCOMMA
EQ_KEY_DIVIDE          = 0xB5
EQ_KEY_NUMPADSLASH     = EQ_KEY_DIVIDE
EQ_KEY_NUMPAD_DIVIDE   = EQ_KEY_DIVIDE
EQ_KEY_SYSRQ           = 0xB7
EQ_KEY_RMENU           = 0xB8
EQ_KEY_RALT            = EQ_KEY_RMENU
EQ_KEY_RIGHT_ALT       = EQ_KEY_RMENU
EQ_KEY_PAUSE           = 0xC5
EQ_KEY_HOME            = 0xC7
EQ_KEY_UP              = 0xC8
EQ_KEY_UPARROW         = EQ_KEY_UP
EQ_KEY_UP_ARROW        = EQ_KEY_UP
EQ_KEY_PRIOR           = 0xC9
EQ_KEY_PGUP            = EQ_KEY_PRIOR
EQ_KEY_PAGE_UP         = EQ_KEY_PRIOR
EQ_KEY_LEFT            = 0xCB
EQ_KEY_LEFTARROW       = EQ_KEY_LEFT
EQ_KEY_LEFT_ARROW      = EQ_KEY_LEFT
EQ_KEY_RIGHT           = 0xCD
EQ_KEY_RIGHTARROW      = EQ_KEY_RIGHT
EQ_KEY_RIGHT_ARROW     = EQ_KEY_RIGHT
EQ_KEY_END             = 0xCF
EQ_KEY_DOWN            = 0xD0
EQ_KEY_DOWNARROW       = EQ_KEY_DOWN
EQ_KEY_DOWN_ARROW      = EQ_KEY_DOWN
EQ_KEY_NEXT            = 0xD1
EQ_KEY_PGDN            = EQ_KEY_NEXT
EQ_KEY_PAGE_DOWN       = EQ_KEY_NEXT
EQ_KEY_INSERT          = 0xD2
EQ_KEY_DELETE          = 0xD3
EQ_KEY_LWIN            = 0xDB
EQ_KEY_LEFT_START      = EQ_KEY_LWIN
EQ_KEY_RWIN            = 0xDC
EQ_KEY_RIGHT_START     = EQ_KEY_RWIN
EQ_KEY_APPS            = 0xDD
EQ_KEY_POWER           = 0xDE
EQ_KEY_SLEEP           = 0xDF
EQ_KEY_WAKE            = 0xE3
EQ_KEY_WEBSEARCH       = 0xE5
EQ_KEY_WEB_SEARCH      = EQ_KEY_WEBSEARCH
EQ_KEY_WEBFAVORITES    = 0xE6
EQ_KEY_WEB_FAVORITES   = EQ_KEY_WEBFAVORITES
EQ_KEY_WEBREFRESH      = 0xE7
EQ_KEY_WEB_REFRESH     = EQ_KEY_WEBREFRESH
EQ_KEY_WEBSTOP         = 0xE8
EQ_KEY_WEB_STOP        = EQ_KEY_WEBSTOP
EQ_KEY_WEBFORWARD      = 0xE9
EQ_KEY_WEB_FORWARD     = EQ_KEY_WEBFORWARD
EQ_KEY_WEBBACK         = 0xEA
EQ_KEY_WEB_BACK        = EQ_KEY_WEBBACK
EQ_KEY_MYCOMPUTER      = 0xEB
EQ_KEY_MY_COMPUTER     = EQ_KEY_MYCOMPUTER
EQ_KEY_MAIL            = 0xEC
EQ_KEY_MEDIASELECT     = 0xED
EQ_KEY_MEDIA_SELECT    = EQ_KEY_MEDIASELECT
