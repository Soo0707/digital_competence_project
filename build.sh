#!/bin/bash

# TARGET LINUX
# only works if sqlite is already built
# if headers were provided by the distro package manager, change #include "sqlite3.h" to #include <sqlite3.h>
# g++ main.cpp -o /mnt/tmpfs/a.out -lsqlite3

# TARGET WINDOWS

x86_64-w64-mingw32-gcc -c sqlite3.c -o lib/sqlite3.o # build sqlite with C, obtained from the amalgamation package on sqlite's site
x86_64-w64-mingw32-ar rcs lib/libsqlite3.a lib/sqlite3.o # turn blob to archive
x86_64-w64-mingw32-g++ main.cpp -o /mnt/tmpfs/out.exe -Iinclude/ -Llib/ -lsqlite3 -static # build project with sqlite
