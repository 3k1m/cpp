Linux C++ Program Runner 

(c) Mike Lindstrom 2022 under GNU Affero General Public License v3.0

## Overview

This program can be used on a Linux OS to compile and run a collection of C++ source files stored in separate directories. Overall, it:
(1) Takes common files (such as a makefile, input files, provided source files) and places them into each separate submission directory, possibly overwriting the files 
(2) Compiles each program based on the makefile, storing the compilation results in a file "compiler_output.txt" 
(3) Runs each program based on a run command, storing the result in a file "program_output.txt" 
(4) And limits each program's runtime (in case of slow code or infinite loops).

## How to run

By default, you will need the following:

1. A directory with the files common to all submissions (by default this is called "Common") -- this directory must contain a makefile  
2. A directory storing directories of source code submissions (by default this is called "Submissions") 
3. A file specifying the how the programs are to be run (by default this is "run.txt") 

After this, one simply runs the program and it will attempt to compile and run each program.

> ./auto_run

## Command line arguments and examples 

### -tX 

This flag can be used to change the number of seconds each running program is limited by to X seconds. By default it is 2 seconds. For example:

> ./auto_run -t7

will give each program 7 seconds to run 

### -cX 

This flag can be used to change the path of the directory containing the common files to X. For example:

> ./auto_run -c../Includes

When not specified, X is 'Common'.

### -sX 

This flag can be used to change the path of the directory containing the submissions to X. For example:

> ./auto_run -sHomework3/Submissions

When not specified, X is 'Submissions'.

### -rX

This flag can be used to specify the name (and path) of the file to use for executing the programs. For example:

> ./auto_run -rRunThis.txt

When not specified, X is 'run.txt'.

### Combining stems 

The flags can easily be combined and the order does not matter. For example:

> ./auto_run -sHomework3/ -t120 -cIncludes
