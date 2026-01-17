#include <cstdint>


#define SHIFT 0x02

#define HID_KEYBOARD 0x03C1



// Standard HID Report Descriptor for Keyboard
static const uint8_t reportMap[] = {
    0x05, 0x01, // USAGE_PAGE (Generic Desktop)
    0x09, 0x06, // USAGE (Keyboard)
    0xa1, 0x01, // COLLECTION (Application)
    0x85, 0x01, //   REPORT_ID (1)
    0x05, 0x07, //   USAGE_PAGE (Keyboard)
    0x19, 0xe0, //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7, //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00, //   LOGICAL_MINIMUM (0)
    0x25, 0x01, //   LOGICAL_MAXIMUM (1)
    0x75, 0x01, //   REPORT_SIZE (1)
    0x95, 0x08, //   REPORT_COUNT (8)
    0x81, 0x02, //   INPUT (Data,Var,Abs)
    0x95, 0x01, //   REPORT_COUNT (1)
    0x75, 0x08, //   REPORT_SIZE (8)
    0x81, 0x03, //   INPUT (Cnst,Var,Abs)
    0x95, 0x05, //   REPORT_COUNT (5)
    0x75, 0x01, //   REPORT_SIZE (1)
    0x05, 0x08, //   USAGE_PAGE (LEDs)
    0x19, 0x01, //   USAGE_MINIMUM (Num Lock)
    0x29, 0x05, //   USAGE_MAXIMUM (Kana)
    0x91, 0x02, //   OUTPUT (Data,Var,Abs)
    0x95, 0x01, //   REPORT_COUNT (1)
    0x75, 0x03, //   REPORT_SIZE (3)
    0x91, 0x03, //   OUTPUT (Cnst,Var,Abs)
    0x95, 0x06, //   REPORT_COUNT (6)
    0x75, 0x08, //   REPORT_SIZE (8)
    0x15, 0x00, //   LOGICAL_MINIMUM (0)
    0x25, 0x65, //   LOGICAL_MAXIMUM (101)
    0x05, 0x07, //   USAGE_PAGE (Keyboard)
    0x19, 0x00, //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65, //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00, //   INPUT (Data,Ary,Abs)
    0xc0        // END_COLLECTION
};

struct KeyMap {
    uint8_t key;
    uint8_t modifier;
};

// Shift modifier shorthand
#define KEY_LEFT_CTRL 0x01
#define KEY_LEFT_SHIFT 0x02
#define KEY_LEFT_ALT 0x04
#define KEY_LEFT_GUI 0x08
#define KEY_RIGHT_CTRL 0x10
#define KEY_RIGHT_SHIFT 0x20
#define KEY_RIGHT_ALT 0x40
#define KEY_RIGHT_GUI 0x80
#define KEY_ENTER 0x28

const KeyMap ascii_to_hid[128] = {
    {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},         // 0-7
    {0x2a, 0}, {0x2b, 0}, {0x28, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, // 8-15 (8:BS, 9:TAB, 10:ENTER)
    {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},         // 16-23
    {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},         // 24-31
    {0x2c, 0},      // 32: Space
    {0x1e, KEY_LEFT_SHIFT},  // 33: !
    {0x34, KEY_LEFT_SHIFT},  // 34: "
    {0x20, KEY_LEFT_SHIFT},  // 35: #
    {0x21, KEY_LEFT_SHIFT},  // 36: $
    {0x22, KEY_LEFT_SHIFT},  // 37: %
    {0x24, KEY_LEFT_SHIFT},  // 38: &
    {0x34, 0},      // 39: '
    {0x26, KEY_LEFT_SHIFT},  // 40: (
    {0x27, KEY_LEFT_SHIFT},  // 41: )
    {0x25, KEY_LEFT_SHIFT},  // 42: *
    {0x2e, KEY_LEFT_SHIFT},  // 43: +
    {0x36, 0},      // 44: ,
    {0x2d, 0},      // 45: -
    {0x37, 0},      // 46: .
    {0x38, 0},      // 47: /
    {0x27, 0},      // 48: 0
    {0x1e, 0},      // 49: 1
    {0x1f, 0},      // 50: 2
    {0x20, 0},      // 51: 3
    {0x21, 0},      // 52: 4
    {0x22, 0},      // 53: 5
    {0x23, 0},      // 54: 6
    {0x24, 0},      // 55: 7
    {0x25, 0},      // 56: 8
    {0x26, 0},      // 57: 9
    {0x33, KEY_LEFT_SHIFT},  // 58: :
    {0x33, 0},      // 59: ;
    {0x36, KEY_LEFT_SHIFT},  // 60: <
    {0x2e, 0},      // 61: =
    {0x37, KEY_LEFT_SHIFT},  // 62: >
    {0x38, KEY_LEFT_SHIFT},  // 63: ?
    {0x1f, KEY_LEFT_SHIFT},  // 64: @
    {0x04, KEY_LEFT_SHIFT}, {0x05, KEY_LEFT_SHIFT}, {0x06, KEY_LEFT_SHIFT}, {0x07, KEY_LEFT_SHIFT}, {0x08, KEY_LEFT_SHIFT}, // 65-69: A-E
    {0x09, KEY_LEFT_SHIFT}, {0x0a, KEY_LEFT_SHIFT}, {0x0b, KEY_LEFT_SHIFT}, {0x0c, KEY_LEFT_SHIFT}, {0x0d, KEY_LEFT_SHIFT}, // 70-74: F-J
    {0x0e, KEY_LEFT_SHIFT}, {0x0f, KEY_LEFT_SHIFT}, {0x10, KEY_LEFT_SHIFT}, {0x11, KEY_LEFT_SHIFT}, {0x12, KEY_LEFT_SHIFT}, // 75-79: K-O
    {0x13, KEY_LEFT_SHIFT}, {0x14, KEY_LEFT_SHIFT}, {0x15, KEY_LEFT_SHIFT}, {0x16, KEY_LEFT_SHIFT}, {0x17, KEY_LEFT_SHIFT}, // 80-84: P-T
    {0x18, KEY_LEFT_SHIFT}, {0x19, KEY_LEFT_SHIFT}, {0x1a, KEY_LEFT_SHIFT}, {0x1b, KEY_LEFT_SHIFT}, {0x1c, KEY_LEFT_SHIFT}, {0x1d, KEY_LEFT_SHIFT}, // 85-90: U-Z
    {0x2f, 0},      // 91: [
    {0x31, 0},      // 92: \ (Backslash)
    {0x30, 0},      // 93: ]
    {0x23, KEY_LEFT_SHIFT},  // 94: ^
    {0x2d, KEY_LEFT_SHIFT},  // 95: _
    {0x35, 0},      // 96: `
    {0x04, 0}, {0x05, 0}, {0x06, 0}, {0x07, 0}, {0x08, 0}, // 97-101: a-e
    {0x09, 0}, {0x0a, 0}, {0x0b, 0}, {0x0c, 0}, {0x0d, 0}, // 102-106: f-j
    {0x0e, 0}, {0x0f, 0}, {0x10, 0}, {0x11, 0}, {0x12, 0}, // 107-111: k-o
    {0x13, 0}, {0x14, 0}, {0x15, 0}, {0x16, 0}, {0x17, 0}, // 112-116: p-t
    {0x18, 0}, {0x19, 0}, {0x1a, 0}, {0x1b, 0}, {0x1c, 0}, {0x1d, 0}, // 117-122: u-z
    {0x2f, KEY_LEFT_SHIFT},  // 123: {
    {0x31, KEY_LEFT_SHIFT},  // 124: |
    {0x30, KEY_LEFT_SHIFT},  // 125: }
    {0x35, KEY_LEFT_SHIFT},  // 126: ~
    {0, 0}          // 127: DEL
};