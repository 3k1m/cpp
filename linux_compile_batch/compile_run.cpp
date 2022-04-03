/**
@file compile_run.cpp 
@brief compiles a set of programs and runs them, storing the compilation and program outputs   
@author Mike Lindstrom
@version 1.0
@date Apr 2022
@copyright under GNU Affero General Public License v3.0
@details based on user choices or defaults, the program does the following:
(1) moves common files into each submission directory 
(2) compiles each program in the submission directory with a makefile and other common files and then stores the result 
(3) runs each program in the submission directory and stores the result 
NOTE: this works for Linux and OS's that support Linux commands 
*/

#include "CppLinux.h"

int main(int argc, char* argv[]){
	static constexpr int max_arg = 5; // 4 inputs + script 
	if(argc>max_arg){
		runs::handle_badness("too many arguments");
	}	  
	
	std::string common_directory{"./Common"};
	std::string run_file{"./run.txt"};
	std::string submission_directory{"./Submissions"};
	int max_sec = 2; 
	
	static constexpr size_t offset = 2;
	for(int i=1; i < argc; ++i){
		if(argv[i][0] != '-'){ // check the stem is there for format 
			runs::handle_badness("missing - stem in argument");
		}
		switch(argv[i][1]){ // can be 'c', 'r', 's', or 't'
			case 'c':
			common_directory = argv[i]+offset; break;
			case 'r':
			run_file = argv[i]+offset; break;
			case 's':
			submission_directory = argv[i]+offset; break;
			case 't':
			max_sec = std::stoi(argv[i]+offset); break;
			default:
			runs::handle_badness("incorrect argument");		  
		}
	}
 
	// the files to include 
	auto include_files = runs::get_all_common_files(common_directory);
  
	// the command to run 
	const std::string command = runs::get_command(run_file);    
  
	// put common files into submssion folders   
	runs::include_commons(submission_directory, include_files); 
  
	// run make and execute 
	runs::make_and_run(submission_directory, command, max_sec);
  
	return 0;
}
