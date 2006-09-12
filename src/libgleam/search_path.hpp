
#ifndef GLEAM_SEARCH_PATH_INCLUDED
#define GLEAM_SEARCH_PATH_INCLUDED

#include <string>
#include <vector>

namespace gleam {

using std::string;
using std::vector;

/**
 * The SearchPath class is a helper class for getting a vector of absolute
 * paths contained in a search path string where a "search path string" contains
 * absolute directory paths separated by a colon(:) or a semi-colon(;)
 * on windows.
 */
class SearchPath {
public:

	/**
	 * Create an empty SearchPath.
	 */
	SearchPath ();

	/**
	 * Initialize SearchPath from a string, each absolute path contained
	 * in the "path" will be accessed to ensure it exists and is readable.
	 * 
	 * \param search_path A path string.
	 */
	SearchPath (const string& search_path);

	/**
	 * Initialize SearchPath from a vector of path strings, each absolute
	 * path contained in paths will be accessed to ensure it exists and 
	 * is readable.
	 * 
	 * \param path A path string.
	 */
	SearchPath (const vector<string>& paths);

	/**
	 * The copy constructor does what you would expect and copies the
	 * vector of paths contained by the SearchPath.
	 */
	SearchPath (const SearchPath& search_path);

	/**
	 * Indicate whether there are any directories in m_dirs, if SearchPath 
	 * is initialized with an empty string as the result of for instance 
	 * calling Glib::getenv where the environment variable doesn't exist 
	 * or if none of the directories in the search_path string are 
	 * accessible then false is returned.
	 *
	 * \return true if there are any paths in m_paths.
	 */
	operator void* () const { return (void*)!m_dirs.empty(); }
		
	/**
	 * \return vector containing the absolute paths to the directories 
	 * contained in the SearchPath.
	 */
	operator const vector<string>& () const { return m_dirs; }
	
	/**
	 * \return vector containing the absolute paths to the directories 
	 * contained in the SearchPath.
	 */
	const vector<string>& dirs () const { return m_dirs; }

	/**
	 * \return a search path string.
	 *
	 * The string that is returned contains the platform specific
	 * path separator. The verbosity and "explicitness" of this 
	 * method is indicitive that I don't think it should be used
	 * that often.
	 */
	const string get_search_path_string () const;

	// XXX todo, fix the operator situation.
	const SearchPath& operator= (const SearchPath& path);

	/**
	 * Add another path to the search path.
	 */
	const SearchPath& operator+= (const string& directory_path);

	/**
	 * Add a sub-directory to each path in the search path.
	 */
	SearchPath& add_subdirectory_to_path (const string& subdir);

protected:
	
	friend const SearchPath operator+ (const SearchPath&, const SearchPath&);

	bool readable_directory (const string& directory_path);

	void add_readable_directory (const string& directory_path);

	void add_readable_directories (const vector<string>& paths);
	
	vector<string> m_dirs;

};

/**
 * \return true If file is found in the SearchPath, false if the file
 * wasn't found or more than a single file name with the name filename
 * was found.
 */
bool find_file_in_search_path (const SearchPath& path, 
                               const string& filename,
                               string& resulting_path_to_file);

} // namespace gleam

#endif // GLEAM_SEARCH_PATH_INCLUDED
