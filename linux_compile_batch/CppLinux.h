/**
@file CppLinux.h 
@brief declares functions necessary for compiling and running batches of source code in Linux 
@author Mike Lindstrom
@version 1.0
@date Apr 2022
@copyright under GNU Affero General Public License v3.0
*/

#ifndef _RUNS__PROGRAMS_
#define _RUNS__PROGRAMS_

#include<vector>
#include<string>

namespace runs{

	/**
	produces a diagnostic printout and terminates
	@param msg what to print
	*/
	[[noreturn]] void handle_badness(const std::string& msg);

	/**
	establishes the common files by scanning directory 
	@param common_path the relative path name for common files 
	@return the string names of all the file paths 
	*/
	[[nodiscard]] std::vector<std::string> get_all_common_files(const std::string& common_path);

	/**
	sets the command for the programs 
	@param run_file the file name -- must be one line  
	@return the run command in that file 
	*/
	[[nodiscard]] std::string get_command(const std::string& run_file);

	/**
	puts the common files into each submission directory 
	@param submissions_path the relative path for where submissions are stored 
	@param include_files the path names of all the files to copy in 
	*/
	void include_commons(const std::string& submissons_path, const std::vector<std::string>& include_files);

	/**
	runs make on all the submissions and runs them with a limited time window
	placing the compiler outut in "compiler_output.txt" and the program output in "program_output.txt" 
	@param submissions_path the path where all the submissions are found
	@param command the command to execute 
	@param max_sec the number of seconds to allot for each indidual run 
	*/
	void make_and_run(const std::string& submissions_path,
		const std::string& command, const int max_sec);

}

#endif 
