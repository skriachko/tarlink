/**
 * @file tar.cpp
 * @brief TAR File Handling Implementation
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


#include "tar.hpp"

#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/stat.h>
#include <vector>
#include <filesystem>


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

void writeTarHeader( std::ofstream& out, const char* filename, size_t filesize )
{
    TarHeader header;

    std::memset( &header, 0, sizeof( TarHeader ) );
    std::strncpy( header.filename, filename, 99 );
    std::sprintf( header.filemode, "%07o", 0644 );
    std::sprintf( header.userid, "%07o", 0 );
    std::sprintf( header.groupid, "%07o", 0 );
    std::sprintf( header.filesize, "%011lo", filesize );
    std::sprintf( header.mtime, "%011lo", 0 );
    header.type = '0'; // Regular file

    // Set checksum field to spaces before calculating checksum
    std::memset( header.checksum, ' ', sizeof( header.checksum ) );

    unsigned char* rawHeader = reinterpret_cast<unsigned char*>( &header );
    unsigned int checksum = 0;

    for ( size_t i = 0; i < sizeof( TarHeader ); ++i )
    {
        checksum += rawHeader[ i ];
    }

    std::sprintf( header.checksum, "%06o", checksum );

    out.write( reinterpret_cast<const char*>( &header ), sizeof( TarHeader ) );
}


void writeFileContents( std::ofstream& out, const std::string& filename )
{
    std::ifstream in( filename, std::ios::binary );
    out << in.rdbuf();

    // TAR files require that file contents be padded to 512 bytes
    auto pos = out.tellp();
    size_t extraBytes = ( tar_padding - ( pos % tar_padding ) ) % tar_padding;
    std::vector<char> padding( extraBytes, 0 );
    out.write( padding.data(), extraBytes );
}


void processPath(std::ofstream& out, const std::filesystem::path& path, const std::filesystem::path& rootPath) {
    if (std::filesystem::is_directory(path)) {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
            if (std::filesystem::is_regular_file(entry.path())) {
                struct stat statbuf;
                if (stat(entry.path().c_str(), &statbuf) != 0) {
                    std::cerr << "Error getting file info for: " << entry.path() << std::endl;
                    continue;
                }

                auto relativePath = std::filesystem::relative(entry.path(), rootPath).string();
                // Remove leading "../" from paths
                size_t pos;
                while ((pos = relativePath.find("../")) != std::string::npos) {
                    relativePath.erase(pos, 3);
                }

                writeTarHeader(out, relativePath.c_str(), statbuf.st_size);
                writeFileContents(out, entry.path().string());
            }
        }
    } else if (std::filesystem::is_regular_file(path)) {
        struct stat statbuf;
        if (stat(path.c_str(), &statbuf) != 0) {
            std::cerr << "Error getting file info for: " << path << std::endl;
            return;
        }

        auto relativePath = std::filesystem::relative(path, rootPath).string();
        // Remove leading "../" from paths
        size_t pos;
        while ((pos = relativePath.find("../")) != std::string::npos) {
            relativePath.erase(pos, 3);
        }

        writeTarHeader(out, relativePath.c_str(), statbuf.st_size);
        writeFileContents(out, path.string());
    } else {
        std::cerr << "Invalid file or directory: " << path << std::endl;
    }
}


void createTarFile( const std::string& tarFilename, const std::vector<std::string>& paths )
{
    std::ofstream out( tarFilename, std::ios::binary );
    std::filesystem::path rootPath = std::filesystem::current_path();

    for ( const auto& pathString : paths )
    {
        std::filesystem::path path = pathString;
        processPath( out, path, rootPath );
    }

    // Write two 512-byte blocks of zeros at the end of the file
    std::vector<char> padding( tar_padding * 2, 0 );
    out.write( padding.data(), tar_padding * 2 );
}


void extractFile( std::ifstream& in, const TarHeader& header, const std::filesystem::path& outputDir )
{
    std::filesystem::path outputPath = outputDir / header.filename;

    // Create directories if they don't exist
    if ( outputPath.has_parent_path() )
    {
        std::filesystem::create_directories( outputPath.parent_path() );
    }

    size_t fileSize;

    sscanf( header.filesize, "%lo", &fileSize );

    std::ofstream out( outputPath, std::ios::binary );

    if ( fileSize > 0 )
    {
        std::vector<char> buffer( fileSize );
        in.read( buffer.data(), fileSize );
        out.write( buffer.data(), fileSize );

        // Skip padding
        in.seekg( ( tar_padding - ( fileSize % tar_padding ) ) % tar_padding, std::ios::cur );
    }
}

void extractTarFile( const std::string& tarFilename, const std::string& outputDir )
{
    std::ifstream in( tarFilename, std::ios::binary );
    TarHeader header;

    while ( in.read( reinterpret_cast<char*>( &header ), sizeof( TarHeader ) ) )
    {
        if ( header.filename[ 0 ] == 0 ) break; // End of archive

        extractFile( in, header, outputDir );
    }
}


} // namespace Tar
