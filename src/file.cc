#include "file.hh"
#include <codecvt>
#include <locale>

File::File() : file() {}

File::File(std::string file) { this->file = file; }

void File::open() {
  if (this->file.empty())
    ERROR_HANDLER("can't open file (name is empty)");

  std::wifstream input(file, std::ios::binary);
  input.imbue(std::locale("fa_IR"));

  std::wstring line;
  while (std::getline(input, line))
    this->lines.push_back(line);

  // when file is empty, this->lines is empty and it leads to occur a bug
  // to prevent this, when a file is empty we append a dummy empty line to it
  if (this->lines.empty())
    this->lines.push_back(L"");
}

void File::save() {
  if (this->file.empty()) // in case no file is opened
    return;               // don't do anything

  std::wofstream output(file);
  output.imbue(std::locale("fa_IR"));

  for (std::wstring line : lines) {
    output << line << '\n';
  }
}

void File::set_file(std::string file) { this->file = file; }

void File::newline_after(size_t row, size_t col) {
  std::wstring &line = this->get(row);

  // insert new line after row, col
  // seek next to indx position
  std::vector<std::wstring>::iterator row_it = this->lines.begin() + row + 1;

  // get the substring from col to the end of the line
  std::wstring newline = line.substr(col);
  line = line.substr(0, col);

  // insert the new line
  this->lines.insert(row_it, newline);
}

void File::jointo_nextline(size_t row) {
  std::wstring &line = this->get(row);
  std::wstring nextline = this->get(row + 1);

  // append next line to the current one
  line += nextline;

  // seek to the next line to remove it
  std::vector<std::wstring>::iterator it = this->lines.begin() + row + 1;
  this->lines.erase(it);
}

size_t File::jointo_prevline(size_t row) {
  std::wstring line = this->get(row);
  std::wstring &prevline = this->get(row - 1);

  // store prevline size and return it to update cursor_y
  size_t ret = prevline.size();

  // append current line to the previous line
  prevline += line;

  // remove current line
  std::vector<std::wstring>::iterator it = this->lines.begin() + row;
  this->lines.erase(it);

  return ret;
}

std::wstring &File::get(size_t indx) { return this->lines[indx]; }

size_t File::size() { return this->lines.size(); }

bool File::is_empty() { return this->file.empty(); }
