/**
 * @file tar.hpp
 * @brief TAR File API
 *
 * This file contains API for creating and extracting TAR archives.
 * It supports handling of files and directories, preserving the directory
 * structure in the archives.
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


#pragma once

#include <string>
#include <vector>

namespace Tar {

constexpr uint32_t tar_padding = 512;


struct TarHeader
{
    char filename[ 100 ];
    char filemode[ 8 ];
    char userid[ 8 ];
    char groupid[ 8 ];
    char filesize[ 12 ];
    char mtime[ 12 ];
    char checksum[ 8 ];
    char type;
    char linkedfile[ 100 ];
    char padding[ 255 ]; // Padding to make the header 512 bytes
};


void createTarFile( const std::string& tarFilename, const std::vector<std::string>& filenames );
void extractTarFile( const std::string& tarFilename, const std::string& outputDir );

}
