#ifndef DEFINES_HH_
#define DEFINE_HH_

#include <iostream>

#define CTRL_KEY(key) (key & 0x1F) // 00011111 -> ctrl is pressed

#define ERROR_HANDLER(msg) \
do { \
    std::cout << "\x1b[2J"; \
    std::cout << "\x1b[H"; \
    std::cerr << msg; \
    exit(1); \
} while (false) \

#endif // DEFINES_H_