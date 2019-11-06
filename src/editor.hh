#ifndef EDITOR_HH_
#define EDITOR_HH_

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

    void set_file(std::string);
    void refresh_screen();
    void draw_rows();
    void process_key();
};

#endif // EDITOR_HH_