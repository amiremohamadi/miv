#ifndef DEFINES_HH_
#define DEFINES_HH_

#include <iostream>
#include <string>

#define VERSION "0.0.1"

#define CTRL_KEY_DOWN 531
#define CTRL_KEY_UP 574
#define CTRL_KEY_RIGHT 568
#define CTRL_KEY_LEFT 553
#define KEY_ESC '\x1b'

#define CTRL_KEY(key) (key & 0x1F) // 00011111 -> ctrl is pressed

#define ERROR_HANDLER(msg) \
do { \
    std::cout << "\x1b[2J"; \
    std::cout << "\x1b[H"; \
    std::cerr << msg; \
    exit(1); \
} while (false) \

static std::string messages[] = {
    "MIV -- easier than vim",
    "VERSION " VERSION,
    "by @amiremohamadi"
};

// enum index for color pairs
enum ColorPairs {
    BLACK_WHITE = 0,
    BLACK_BLUE,
    BLACK_RED,
};

#endif // DEFINES_HH_
