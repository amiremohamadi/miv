#include "editor.hh"

int main() {
  Editor editor;

  while (true) {
    editor.refresh_screen();
    editor.process_key();
  }

  return 0;
}