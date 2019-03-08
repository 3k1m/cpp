**Memory Leaks (for Visual Studio)**

This allows for a simple and very *un*-sophisticated way for debugging memory leaks. The code works in Visual Studio 2017. Due to its simplicity and some compiler-dependent options, it is not valid for Clang or gcc.

There are better alternatives out there. These files were put together for something quick and dirty. No guarantees are made as to whether
certain memory allocation strategies can 'fool' this leak checker but it seemingly works for new/delete expressions.
