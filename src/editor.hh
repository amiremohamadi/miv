#ifndef EDITOR_HH_
#define EDITOR_HH_

#include "config.hh"
#include "file.hh"
#include <ncursesw/curses.h>
#include <string>

class Editor {
private:
  WINDOW *window;
  File file;
  static Config config;
  void _create_win(int, int, int, int);
  void _delete_win();
  void _win_resize();
  void _move_cursor(wchar_t);
  void _scroll();

public:
  Editor();
  ~Editor();

  void set_file(std::string);
  void refresh_screen();
  void draw_rows();
  void insert_char(wchar_t);
  void remove_char(bool);
  void insert_newline();
  void process_key();
};

#endif // EDITOR_HH_
