#include "file.hh"

File::File() : file() {}

File::File(std::string file) {
  this->file = file;
}

void File::open() {
  if (this->file.empty())
    ERROR_HANDLER("can't open file (name is empty)");

  std::ifstream input(file);

  std::string line;
  while (std::getline(input, line)) this->lines.push_back(line);

  // when file is empty, this->lines is empty and it leads to occur a bug
  // to prevent this, when a file is empty we append a dummy empty line to it 
  if (this->lines.empty()) this->lines.push_back(""); 
}

void File::save() {
    if (this->file.empty()) // in case no file is opened
        return; // don't do anything
    
    std::ofstream output(file);
    
    for (std::string line : lines) {
        output << line << '\n';
    }
}

void File::set_file(std::string file) {
  this->file = file;
}

std::string &File::get(size_t indx) {
  return this->lines[indx];
}

size_t File::size() {
  return this->lines.size();
}

bool File::is_empty() {
  return this->file.empty();
}
