#ifndef CONFIG_HH_
#define CONFIG_HH_

#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "defines.hh"

struct Config {
  termios orig_termios; // original termios settings
  unsigned int cursor_x, cursor_y; // cursor position
  unsigned int row_size, col_size;
  unsigned int row_offset, col_offset;

  Config() {
    winsize window_size;

    // enable_rawmode()
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size) == -1 || window_size.ws_col == 0)
        ERROR_HANDLER("error while init editor (get row, col sizes)\n");
    
    this->cursor_x = this->cursor_y = 0;
    this->col_size = window_size.ws_col;
    this->row_size = window_size.ws_row;
    this->row_offset = this->col_offset = 0;
  }
};

#endif // CONFIG_HH_