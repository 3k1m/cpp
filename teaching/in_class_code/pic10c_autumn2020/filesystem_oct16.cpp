#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem; // abbreviate std::filesystem
int main() {
	try { // might already exist
		fs::create_directories("../foo/bar/bazzz");
	}
	catch (const fs::filesystem_error & E) { // catch the exceptions
	}
	try { // might already exist
		fs::create_directories("../foo/bar/to_remove");
	}
	catch (const fs::filesystem_error & E) { // catch the exceptions
	}
	std::ofstream("../foo/bar/to_remove/file.txt");
	fs::remove_all("../foo/bar/to_remove"); // not empty!
	std::ofstream("../foo/bar/file1.txt");
	std::ofstream("../foo/bar/file2.txt");
	std::ofstream("file3.txt");

	if (fs::exists("../foo/bar/file3.txt")) { // file already exists?
		fs::remove("../foo/bar/file3.txt");
	}
	fs::copy("file3.txt", "../foo/bar/"); // now safe to copy
	if (fs::exists("../foo/bar/baz")) { // directory already exists?
		fs::remove("../foo/bar/baz");
	}
	fs::rename("../foo/bar/bazzz", "../foo/bar/baz");
	fs::directory_iterator iter("../foo/bar");
	for (const auto& p : iter) { // each path
		if (p.is_regular_file()) { // a file
			std::cout << "file: " << p.path() << '\n';
		}
		else if (p.is_directory()) { // a directory
			std::cout << "directory: " << p.path().string() << '\n';
		}
		else { // should not happen here
			std::cout << "something else: " << p.path() << '\n';
		}
	}
	return 0;
}
