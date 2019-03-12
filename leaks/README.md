**Memory Leaks**

This allows for a simple and very *un*-sophisticated way for debugging memory leaks. The code works in Visual Studio 2017, with Clang 7.0.0, and on gcc 7.2.0.

There are better alternatives out there. These files were put together for something quick and dirty. No guarantees are made as to whether
certain memory allocation strategies can 'fool' this leak checker but it seemingly works for new/delete expressions.
