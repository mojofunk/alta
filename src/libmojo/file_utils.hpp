
#ifndef MOJO_FILE_UTILS_INCLUDED
#define MOJO_FILE_UTILS_INCLUDED

#include <vector>
#include <string>
//#include <cstddef> // for std::size_t

#include <boost/filesystem/path.hpp>

namespace mojo {

using std::vector;
using std::string;
using boost::filesystem::path;

/**
 * Convert a vector of boost::filesystem::path representations
 * of a filesystem path to a string representation of a path.
 */
vector<string>
paths_to_strings(const vector<path>& paths);

/**
 * Convert a vector containing string representations of paths
 * to a vector containing the boost::filesystem::path 
 * representations
 */ 
vector<path>
strings_to_paths(const vector<string>& paths);

/**
 * \return true if the filename matches
 */
typedef bool (*FileMatchFunc)(const string& filename);

std::size_t
find_matching_files (const vector<path>& directory_paths,
                     FileMatchFunc match_functor,
                     vector<path>& result);

std::size_t
find_matching_files (const path& directory_path,
                     FileMatchFunc match_functor,
                     vector<path>& result);

} // namespace mojo

#endif // MOJO_FILE_UTILS_INCLUDED
