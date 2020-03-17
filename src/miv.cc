#include "editor.hh"

int main(int argc, char **argv) {
  Editor editor;

  if (argc >= 2) {
    editor.set_file(argv[1]);
  }

  while (true) {
    editor.refresh_screen();
    editor.process_key();
  }

  return 0;
}
