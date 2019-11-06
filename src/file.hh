#ifndef FILE_HH_
#define FILE_HH_

#include <string>
#include <fstream>
#include <vector>
#include "defines.hh"

class File {
  private:
    std::string file;
    std::vector<std::string> lines;

  public:
    File();
    File(std::string);

    void open();
    void set_file(std::string);
    std::string get(size_t);
    size_t size();
    bool is_empty();
};

#endif // FILE_HH_