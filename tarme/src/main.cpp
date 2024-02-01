/**
 * @file main.cpp
 * @brief TARME tool uses tarlink lib and can be used to archive and extract
 * TAR files.
 *
 * This is a tool to create and extract TAR archives.
 * It supports handling of files and directories, preserving the directory
 * structure in the archives.
 *
 * Usage:
 * - Creating a TAR archive: ./tarme --create <output.tar> <path1> <path2> ...
 *   path can be either directory or file.
 *
 * - Extracting a TAR archive: ./tarme --extract <tarfile> <outputDir>
 *
 * @author Sergii Kriachko
 * @date 01-02-2024
 *
 * Licensed under the MIT License (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    https://opensource.org/licenses/MIT
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "tar.hpp"

#include <iostream>
#include <string>
#include <vector>

int main( int argc, char* argv[] )
{
    if ( argc < 3 )
    {
        std::cerr << "Usage:\n"
                  << "  To create a tar archive: " << argv[ 0 ] << " --create <output.tar> <path1> [path2] ...\n"
                  << "    <path> can be a file or a directory. Directories are added recursively.\n"
                  << "  To extract a tar archive: " << argv[ 0 ] << " --extract <tarfile> <outputDir>\n"
                  << std::endl;
        return 1;
    }

    std::string cmd = argv[ 1 ];

    if ( cmd == "--create" )
    {
        if ( argc < 4 )
        {
            std::cerr << "Usage for creating a tar archive: " << argv[ 0 ] << " --create <output.tar> <path1> [path2] ...\n";
            return 1;
        }

        std::string tarFilename = argv[ 2 ];
        std::vector<std::string> files( argv + 3, argv + argc );
        Tar::createTarFile( tarFilename, files );

        std::cout << "Created TAR file " << tarFilename << std::endl;
    }
    else if ( cmd == "--extract" )
    {
        if ( argc != 4 )
        {
            std::cerr << "Usage for extracting a tar archive: " << argv[ 0 ] << " --extract <tarfile> <outputDir>\n";
            return 1;
        }

        std::string tarFilename = argv[ 2 ];
        std::string outputDir = argv[ 3 ];
        Tar::extractTarFile( tarFilename, outputDir );

        std::cout << "Extracted TAR file " << tarFilename << " to " << outputDir << std::endl;
    }
    else
    {
        std::cerr << "Invalid command. Use --create or --extract." << std::endl;
        return 1;
    }

    return 0;
}



