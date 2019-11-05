#ifndef EDITOR_H_
#define EDITOR_H_

#include <string>
#include <ncurses.h>
#include "config.hh"
#include "file.hh"

class Editor {
  private:
    WINDOW *window;
    File file;
    static Config config;
    void create_win(int, int, int, int);
    void delete_win();
    void win_resize();
    void move_cursor(wchar_t);
 

  public:
    Editor();
    void refresh_screen();
    void draw_rows();
    void process_key();
};

#endif // EDITOR_H_