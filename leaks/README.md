#Memory Leaks

These files allow for a simple and very *un*-sophisticated way for debugging memory leaks. The code works in Visual Studio 2017 and in g++
(for C++11 and perhaps later).

There are better alternatives out there. These files were put together for something quick and dirty. No guarantees are made as to whether
certain memory allocation strategies can 'fool' this leak checker but it seemingly works for new/delete expressions.
