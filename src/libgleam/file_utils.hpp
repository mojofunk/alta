
#ifndef GLEAM_FILE_UTILS_INCLUDED
#define GLEAM_FILE_UTILS_INCLUDED

#include <string>
#include <vector>

namespace Glib {
	class PatternSpec;
}

namespace gleam {

using std::string;
using std::vector;

const string path_delimiter();

/**
 *
 */
const string
operator/ (const string& base_path, const string& path_element);

/**
  Get a list of files names in a directory.
  
  \note You must join path with result to get the absolute path
  to the file. \see Glib::build_filename
  
  \param path An Absolute path to a directory
  \param result A vector of filenames.
  */
void
get_files_in_directory (const string& path,
                        vector<string>& result);

/**
    Takes a number of paths and returns all the files matching
    a particular pattern.

    \param paths A vector containing the Absolute paths
    \param pattern A Glib::PatternSpec used to match the files.
    \param result A vector in which to place the resulting matches.
    to the matching files, if false just the filename.
*/
void
find_matching_files (const vector<string>& paths,
                     const Glib::PatternSpec& pattern,
                     vector<string>& result);

/**
    Takes a single string that is a concatenated list of paths
    separated by either a colon or semi-colon depending on the 
    platform and puts a list of all the resulting files in the 
    result vector. \see find_matching_files
*/
void
find_matching_files_in_search_path (const string& path,
                                    const Glib::PatternSpec& pattern,
                                    vector<string>& result);

/**
 * Takes a search path and a file name and places the full path
 * to that file if it is found within the search path in result.
 *
 * \return true If file is found within the search path, false if
 * it isn't found or if more than one file with that name is 
 * found.
 */
bool
find_file_in_search_path (const string& search_path,
                          const string& filename,
                          string& result);
			
/**
 * \return true if a file exists at path and is a regular
 * file, false otherwise.
 */
bool file_exists (const string& path);

/**
 * \return true if file is writable
 */
bool file_is_writable (const string& path);

/**
 * \return true if file at path is empty
 */
bool file_is_empty (const string& path);

/**
 * A wrapper around g_access.
 * \return true if file at path exists and
 * matches the file permissions.
 */
bool access_file (const string& path, int mode);

/**
 * \brief wrapper around the g_rename function.
 * \return true if file was successfully renamed.
 */
bool rename_file (const string& old_path,
		const string& new_path);

/**
 * \return true if a directory exists at path.
 */
bool directory_exists (const string& path);

/**
 * \return true if directory at path is writable
 */
bool directory_is_writable (const string& path);

/**
 * Create a directory at path with the default permissions
 * \return true if directory was able to be created or 
 * already exists, false if an error occured and the
 * directory could not be created.
 */
bool create_directory (const string& path);

/**
 * \return true if newer_file has been more recently modified
 * than older_file
 */
bool file_is_more_recently_modified (const string& newer_file,
                                     const string& older_file);

} // namespace gleam

#endif // GLEAM_FILE_UTILS_INCLUDED
