#ifndef FILE_HH_
#define FILE_HH_

#include "defines.hh"
#include <fstream>
#include <string>
#include <vector>

class File {
private:
  std::string file;
  std::vector<std::wstring> lines;

public:
  File();
  File(std::string);

  void open();
  void save();
  void set_file(std::string);
  void newline_after(size_t, size_t);
  void jointo_nextline(size_t);
  size_t jointo_prevline(size_t);
  std::wstring &get(size_t);
  size_t size();
  bool is_empty();
};

#endif // FILE_HH_
