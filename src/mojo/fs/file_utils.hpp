#ifndef MOJO_FILE_UTILS_H
#define MOJO_FILE_UTILS_H

#include <vector>
#include <string>
//#include <cstddef> // for std::size_t

#include "mojo/fs/filesystem.hpp"

namespace mojo {

using std::vector;
using std::string;

/**
 * \return true if the file matches
 */
typedef bool (*FileMatchFunc)(const fs::path& file_path);

std::size_t
find_matching_files (const vector<fs::path>& directory_paths,
                     FileMatchFunc match_functor,
                     vector<fs::path>& result);

std::size_t
find_matching_files (const fs::path& directory_path,
                     FileMatchFunc match_functor,
                     vector<fs::path>& result);
std::size_t
find_matching_file (const vector<fs::path>& paths,
                    const std::string& filename,
                    vector<fs::path>& result);

std::size_t
find_matching_file (const fs::path& paths,
                    const std::string& filename,
                    vector<fs::path>& result);

bool
find_matching_file (const fs::path& paths,
                    const std::string& filename,
                    fs::path& result);

/**
 * Given a full path to a file that may or may not exist,
 * return a unique non-existing file path.
 */
const fs::path get_non_existent_file_path (const fs::path& file_path);

} // namespace mojo

#endif // MOJO_FILE_UTILS_H
