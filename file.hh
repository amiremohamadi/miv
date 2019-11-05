#ifndef FILE_HH_
#define FILE_HH_

#include <string>

class File {
  private:
    std::string file;

  public:
    File();
    File(std::string);

    bool is_empty();
};

#endif // FILE_HH_