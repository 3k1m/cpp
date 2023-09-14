#include "Writer.h"

#include <sstream>

void Writer::set_lines() {
    std::string line;
    // as long as a line can be read...
    while( std::getline( stream, line) ){
      lines.push_back(line);
    }
    stream.seekg(0); // back to beginning, clear fail
    stream.clear();
  }

  Writer::Writer(const std::string& name) : filename(name),
    stream(filename, std::ios_base::app | std::ios_base::out | std::ios_base::in) { set_lines(); }


  std::string Writer::file_contents() const {
    std::ostringstream oss;
    for(const auto& line : lines ){
      oss << line << '\n';
    }
    return oss.str();
  }

  void Writer::add_line(const std::string& line) {
    stream << line << '\n';
    lines.push_back(line);
  }

  size_t Writer::line_count() const { return lines.size(); }

  const std::string& Writer::file_name() const { return filename; }
