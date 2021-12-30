#Code Plagiairm Detector 

(c) Mike Lindstrom 2021 under GNU Affero General Public License v3.0

## Overview

This code plagiarism detector can work across multiple programming languages. Based on user choices or defaults, the program does the following: 
(1) identify all pairs of directories; 
(2) identifies all suitable files (based on file extension) within those separate directories to compare against the files within all other directories; 
(3) between each pair of directories, all files are compared against each other by each file being tokenized by encoding specially chosen keywords and elements of the language grammar (while ignoring all comments and content within strings);
(4) files are matched to their best matching file in each directory against which they are compared and the directories themselves are scored for similarity;
(5) the distribution of similarity scores is shown and the directories whose similarity matches a sufficient threshold are displayed with their best matching files listed and the regions of overlap displayed.
NOTE 1: this should work across many different programming languages as the format of comments, quotations, keywords, and file extensions are customizable.
NOTE 2: the user can control many features of the program including where the document directories for comparison are stored; where the support files specifying keywords, syntax, etc., are stored; the threshold at which directories should be displayed; the sensitivity of overlap patch for identical content to be deemed significant; the destination of where results should be written to; the similarity scoring mechansism between documents with overlap based on the longest common sequence, longest common subsequence, or longest common sequences split in a greedy fashion without overlap in either document; the ordering of displayed results (increasing or decreasing similarity); the choice of filler for words that are not tokenized; and whether directory similarities are based on the mean or maximum of their corresponding file pairings

## How to run

By default (many customizations are possible), you will need the following:

1. five prepared text files (see the Example folder for an example):
- 'exts.txt' (storing all relevant file extensions for code each on a new line), 
- 'punct.txt' (storing each individual component of grammar for the language like ',', ';', ':', and possibly digits, too), 
- 'keywords.txt' (storing all words that should be parsed by the program such as 'include', 'std', 'console', 'const', etc.),
- 'comments.txt' (defining the start and end of comments on each line in the format [start][end] where 'start' denotes how a comment begins and 'end' denotes how it ends -- if 'end' is blank then 'start' must mean a single line comment)
- 'quotes.txt' (listing the punctuation used in defining strings -- this will likely just be ', ", and possibly `)
2. The exectuable, 'detector', stored in your current working directory
3. A directory called 'Support' in that same directory. The 'Support' directory should have the three text files listed in (1). 
4. A directory called 'Documents' in that same directory. The 'Documents' directory should store all code to be compared, each set of documents should be in their own folder.

After this, one simply runs the program and it will display results to the console and write them to 'res.txt' in a (possibly newly created) 'Results' directory, e.g.

> ./detector

## Command line arguments and examples 

### -dX 

This stem can be used to change the path of the directory containing all folders of source code to X. For example:

> ./detector -d../SubmittedFiles

When not specified, X is 'Documents'.

### -sX 

This stem can be used to change the path of the directory containing the three support files to X. For example:

> ./detector -sCode/Support/

When not specified, X is 'Support'.

### -tX

This stem specifies the fractional threshold X at which and above similar document sequence/subsequence results are printed/stored. For example 

> ./detector -t0.5

When not specified, X is '0.8'.

### -wX 

This stem uses X to determine how how long a common sequence of tokens must be to be counted. For example:

> ./detector -w3

When not specified, X is '0'.

### -rX 

This stem specifies a path and file for writing results to, X. If the directories within the path do not yet exist, they will be created. For example:

> ./detector -r./Output/res.txt 

When not specified, X is './Results/res.txt'. WARNING: do not start the path with '/' as that will then be an absolute path and likely lead to the program crashing due to permission issues.
 
### -uX 

This stem X specifies the type of scoring, longest common sequence, longest common subsequence, or longest common split sequence (allows reordering) used in computing the fractional overlap. The only permissible X values are 'seq' for longest common sequence, 'sub' for longest common subsequence, and 'spl' for the longest common split sequence. For example:

> ./detector -usub

When not specified, X is 'spl'.

### -oX

This stem X specifies the result ordering of most similar documents. The only permissible X values are 'asc' for ascending and 'des' for descending. For example:

> ./detector -odes

When not specified, X is 'asc'.

### -fX

This stem sets the filler for all the words that are not part of the keywords or symbols. For example:

> ./detector -f~~~

When not specified, X is '@'.

### Combining stems 

The stems can easily be combined and the order does not matter. For example:

> ./detector -odes -t0.1 -rResults/res.dat
