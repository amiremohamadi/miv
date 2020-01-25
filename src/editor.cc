#include "editor.hh"

Config Editor::config;

Editor::Editor() : file() {
  setlocale(LC_CTYPE, ""); // UTF-8 support
  initscr();

  use_default_colors();
  start_color();

  // define color pairs
  init_pair(BLACK_BLUE, COLOR_BLUE, -1);

  _create_win(config.row_size, config.col_size, 0, 0);
  keypad(window, TRUE); // enable special keys (like arrow-keys)

  noecho(); // no echo while getch()'ing!
  raw(); // enable raw mode (line buffering desable)

  // restore terminal settings at exit
  std::atexit([](){
    endwin();
  });
}

void Editor::_create_win(int row, int col, int begin_y, int begin_x) {
  window = newwin(row, col, 0, 0);
}

void Editor::_delete_win() {
  delwin(window);
}

void Editor::_win_resize() {
  winsize win;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);

  config.row_size = win.ws_row;
  config.col_size = win.ws_col;
}

void Editor::_move_cursor(wchar_t chr) {
  size_t row_len = !file.is_empty() ? file.get(config.cursor_y).size() : 0;

  switch (chr) {
  case KEY_UP:
    config.cursor_y -= config.cursor_y > 0 ? 1 : 0;
    break;

  case KEY_DOWN:
    config.cursor_y += config.cursor_y < file.size()-1 ? 1 : 0;
    break;

  case KEY_RIGHT:
    config.cursor_x += 1;
    config.dummy_cursor_x = config.cursor_x;
    break;
  
  case KEY_LEFT:
    config.cursor_x -= config.cursor_x > 0 ? 1 : 0;
    config.dummy_cursor_x = config.cursor_x;
    break;

  case KEY_NPAGE:
    config.cursor_y += config.cursor_y+config.row_size < file.size() ?
      config.row_size-1 : (file.size()-config.cursor_y)-1;
    break;

  case KEY_PPAGE:
    config.cursor_y -= config.cursor_y > config.row_size ?
      config.row_size-1 : config.cursor_y;
    break;
  }

  // update row_len with new values
  row_len = !file.is_empty() ? file.get(config.cursor_y).size() : 0;
  if (config.cursor_x > row_len) {
    config.dummy_cursor_x = config.cursor_x;
    config.cursor_x = row_len;
  } else if (config.dummy_cursor_x <= row_len) {
    // using dummy_cursor_x just for having better experience during
    // scrolling! set cursor_x according to previous positions (like vim)
    config.cursor_x = config.dummy_cursor_x;
  }

}

void Editor::_scroll() {
  if (config.cursor_y < config.row_offset)
    config.row_offset = config.cursor_y;
  if (config.cursor_y >= config.row_offset + config.row_size)
    config.row_offset = config.cursor_y - config.row_size + 1;
  if (config.cursor_x < config.col_offset)
    config.col_offset = config.cursor_x;
  if (config.cursor_x >= config.col_offset + config.col_size)
    config.col_offset = config.cursor_x - config.col_size + 1;
}

void Editor::set_file(std::string file) {
  this->file.set_file(file);
  this->file.open();
}

void Editor::refresh_screen() {
  _scroll();

  // reposition the cursor to write tildes
  wmove(window, 0, 0);
  draw_rows();

  // reset cursor position
  wmove(window, (config.cursor_y - config.row_offset), (config.cursor_x - config.col_offset));
  
  // show the cursor  
  wrefresh(window);
}

void Editor::draw_rows() {
  for (int y = 0; y < config.row_size; y++) {
    if (y+config.row_offset < this->file.size()) {
      std::string this_line = file.get(y+config.row_offset);
      
      int len = this_line.length() - config.col_offset;
      if (len < 0) len = 0;
      if (len >= config.col_size) len = config.col_size-1; // TODO: remove this with some shitty tricks

      if (len != 0) wprintw(window, this_line.substr(config.col_offset, len).c_str());
      wprintw(window, "\n");
    } else {
      wprintw(window, "~\n");
    }
  }

  // if no file was opened, print splash messages
  if (this->file.is_empty()) {
    // messages is the array that is placed in defines.hh
    
    wattron(window, COLOR_PAIR(BLACK_BLUE));

    // print the message, center of the screen
    unsigned int i = 0;
    for (std::string message : messages) {
      mvwprintw(window, (config.row_size / 2) + i, 
                (config.col_size / 2) - (message.size() / 2), message.c_str());
      i++;
    }

    wattroff(window, COLOR_PAIR(BLACK_BLUE));
  }
}

void Editor::process_key() {
  wchar_t chr = wgetch(window); // read key

  switch(chr) {
  case CTRL_KEY('q'):
    // exit normally
    exit(0);

  case KEY_RESIZE:
    // resize 
    _win_resize();
    break;

  case KEY_UP:
  case KEY_DOWN:
  case KEY_LEFT:
  case KEY_RIGHT:
  case KEY_NPAGE:
  case KEY_PPAGE:
    _move_cursor(chr);
    break;
  }
}

