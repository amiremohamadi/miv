#include "file.hh"

File::File() : file() {}

File::File(std::string file) {
    this->file = file;
}

bool File::is_empty() {
    return this->file.empty();
}