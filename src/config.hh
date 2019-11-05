#ifndef CONFIG_H_
#define CONFIG_H_

#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "defines.hh"

struct Config {
  termios orig_termios; // original termios settings
  unsigned int cursor_x, cursor_y; // cursor position
  unsigned int row_size, col_size;

  Config() {
    winsize window_size;

    // enable_rawmode()
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size) == -1 || window_size.ws_col == 0)
        ERROR_HANDLER("error while init editor (get row, col sizes)\n");
    
    this->col_size = window_size.ws_col;
    this->row_size = window_size.ws_row;
    this->cursor_x = this->cursor_y = 0;
  }
};

#endif // CONFIG_H_