/**
@file CppLinux.cpp 
@brief defines functions used to compile and run source code through Linux   
@author Mike Lindstrom
@version 1.0
@date Apr 2022
@copyright under GNU Affero General Public License v3.0
*/

#include "CppLinux.h"

#include<stdlib.h>
#include<filesystem>
#include<fstream>
#include<iostream>
#include<string_view>

#include "CppLinux.h"

namespace runs{

	void handle_badness(const std::string& msg){
		std::cerr << msg << '\n';
		std::exit(1);
	}

	std::vector<std::string> get_all_common_files(const std::string& common_path){
	
		namespace fs = std::filesystem;
	
		std::cout << "Establishing the common files..." << std::endl;

		std::vector<std::string> include_files;
	
		// no common path 
		if(!fs::exists(common_path)){
			handle_badness("missing common file path " + common_path);
		}
  
		// get all the common files 
		for(const auto& e : fs::directory_iterator(common_path)){
			std::string inc_file = e.path().string();
			std::cout << "Including " + inc_file << std::endl;
			include_files.push_back(std::move(inc_file));
		}
	
		return include_files;
	}

	std::string get_command(const std::string& run_file){
		std::cout << "Setting command..." << std::endl;
  
		std::ifstream fin(run_file);
		if(!fin){ // missing file 
			handle_badness("missing command file " + run_file);
		}
		std::string command;
		std::getline(fin, command);
		return command;	
	}


	void include_commons(const std::string& submissions_path, const std::vector<std::string>& include_files){
		namespace fs = std::filesystem;
	
		std::cout << "Adding include files to submissions..." << std::endl;
    
		// no path to submissions 
		if(!fs::exists(submissions_path)){
			handle_badness("Missing submissions path " + submissions_path);
		}
  
		// copy all the wanted files 
		for(const std::string& inc : include_files){
			fs::path inc_path(inc);
			const std::string inc_name = inc_path.filename();
	  
			// loop over all directories within submissions 
			for(const auto& sub : fs::directory_iterator(submissions_path)){
				if(sub.is_directory()){
					if(fs::exists(sub.path().string() + '/' + inc_name)){
						fs::remove( sub.path().string() + '/' + inc_name);
					}
					fs::copy(inc, sub.path().string());
				}
			}
		}	
	}

	void make_and_run(const std::string& submissions_path, const std::string& command, const int max_sec){
	
		namespace fs = std::filesystem;
	
		std::cout << "Compiling and running each submission..." << std::endl;
	
		const std::string compiler_dest = "compiler_output.txt";
		const std::string program_dest = "program_output.txt";
	
		// to limit time to max_sec seconds
		const std::string timeout = "timeout " + std::to_string(max_sec) + "s ";
		
		// to preserve directory after cd'ing to run commands 
		const std::string join = " && ";
		
		// to send stderr to same destination as stdout
		const std::string redirect_err = " 2>&1";
	
		for(const auto& sub : fs::directory_iterator(submissions_path)){
			if(sub.is_directory()){
			
				// first clear compiler output 
				const std::string cd = "cd " + sub.path().string();				
		
				std::string cmd = cd + join + "rm -f " + compiler_dest;
				system(cmd.c_str()); // file gone 
			
				// run make and get compiler output  
				cmd = cd + join + "make >> " + compiler_dest + redirect_err;
				system(cmd.c_str());
		
				// clear program output 
				cmd = cd + join + "rm -f " + program_dest;
				system(cmd.c_str()); // file gone 
	  
				// run each program with limited time  
				cmd = cd + join + timeout + command + " >> " + program_dest + redirect_err; 
				system(cmd.c_str()); 	
			}
		}	
	}
}
