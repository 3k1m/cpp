#ifndef _WRITER_
#define _WRITER_

#include<fstream>
#include<string>
#include<vector>

class Writer{
private:
  std::string filename;
  std::fstream stream;
  std::vector<std::string> lines;

  /**
   * sets the lines by reading the file 
   */
  void set_lines();

public:
  /**
   * Makes a Writer object for a file
   * @param name the name of the file to link to 
   */
  Writer(const std::string& name);

  /**
   * gets the file content as a string
   * @return the full file content stored as a string
   */
  std::string file_contents() const;

  /**
   * adds a line to the file
   * @param line the new line of content 
   */
  void add_line(const std::string& line);

  /**
   * counts how many lines are in the file
   * @return how many lines are in the file
   */
  size_t line_count() const;

  /**
   * gets the name of the file linked to
   * @return the name of the file being displayed/written to 
   */
  const std::string& file_name() const;

};

#endif
