
#ifndef BOOTY_FILE_UTILS_INCLUDED
#define BOOTY_FILE_UTILS_INCLUDED

#include <vector>
#include <string>
//#include <cstddef> // for std::size_t

#include <booty/filesystem.hpp>

namespace booty {

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

} // namespace booty

#endif // BOOTY_FILE_UTILS_INCLUDED
