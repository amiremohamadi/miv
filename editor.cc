#include "editor.hh"

Config Editor::config;

Editor::Editor() {
  initscr();
  create_win(config.row_size, config.col_size, 0, 0);
  keypad(window, TRUE); // enable special keys (like arrow-keys)

  noecho(); // no echo while getch()'ing!
  raw(); // enable raw mode (line buffering desable)

  // restore terminal settings at exit
  std::atexit([](){
    endwin();
  });
}

void Editor::create_win(int row, int col, int begin_y, int begin_x) {
  window = newwin(row, col, 0, 0);
}

void Editor::delete_win() {
  delwin(window);
}

void Editor::win_resize() {
  winsize win;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);

  config.row_size = win.ws_row;
  config.col_size = win.ws_col;

  delete_win();
  create_win(config.row_size, config.col_size, 0, 0);
}

void Editor::move_cursor(wchar_t chr) {
  switch (chr) {
  case KEY_UP:
    config.cursor_y -= config.cursor_y > 0 ? 1 : 0;
    break;

  case KEY_DOWN:
    config.cursor_y += config.cursor_y < config.row_size-1 ? 1 : 0;
    break;

  case KEY_RIGHT:
    config.cursor_x += config.cursor_x < config.col_size-1 ? 1 : 0;
    break;
  
  case KEY_LEFT:
    config.cursor_x -= config.cursor_x > 0 ? 1 : 0;
    break;
  }
}

void Editor::refresh_screen() {
  // reposition the cursor to write tildes
  wmove(window, 0, 0);
  draw_rows();

  // reset cursor position
  wmove(window, config.cursor_y, config.cursor_x);
  
  // show the cursor  
  wrefresh(window);
}

void Editor::draw_rows() {
  for (int y = 0; y < config.row_size; y++) {
    wprintw(window, "~\n");
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
    win_resize();
    break;

  case KEY_UP:
  case KEY_DOWN:
  case KEY_LEFT:
  case KEY_RIGHT:
    move_cursor(chr);
    break;
  }
}

