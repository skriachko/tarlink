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


#include <string>
#include <vector>

namespace Tar {

    void createTarFile( const std::string& tarFilename, const std::vector<std::string>& filenames );
    void extractTarFile( const std::string& tarFilename, const std::string& outputDir );

}
