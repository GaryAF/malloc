# malloc
{ EPITECH.} second year project.

Recoding C memory-allocation functions:

    malloc()
    free()
    calloc()
    realloc()

Requirements

    Make
    GCC

Compilation

Navigate to the root of the repository from your Terminal and run make to build the libmy_malloc.so shared library.
How to use the functions?
On Linux

To replace the default memory-allocation functions with our functions, execute those commands:

LD_LIBRARY_PATH=$(pwd)
LD_PRELOAD=/path/to/our/library/libmy_malloc.so ./path/to/your/c/program
