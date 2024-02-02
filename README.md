# tarlink

`tarlink` is a lightweight, easy-to-use C++ library for creating and extracting TAR archives. It offers a straightforward interface for handling TAR files, enabling the archiving of multiple files and directories into a single TAR file, as well as the extraction of contents from TAR archives.

# tarme

`tarme` is a command-line tool for creating and extracting TAR files. It uses the "tarlink" library, which provides a simple C++ interface to archive multiple files and directories into a TAR format and to extract files from TAR archives.

## Features

- Create TAR archives from files and directories, with directory structure preservation.
- Extract TAR archives.

## Building with CMake

Ensure you have a C++17 compatible compiler and CMake installed.

1. Navigate to the `tarlink` project directory.

2. Create a build directory and navigate into it:
   ```bash
   mkdir build ; cd build

3. Build it:
   ```bash
   cmake .. ; make

## How to use tarme

 Creating a TAR archive:
   ```bash
   tarme --create <output.tar> <path1> <path2> ...
path can be either directory or file.

### For example: create a myarchive.tar from directory ./MYFILES
   ```bash
   tarme --create myarchive.tar ./MYFILES

### Extracting a TAR archive myarchive.tar into current directory:
   ```bash
tarme --extract myarchive.tar .
