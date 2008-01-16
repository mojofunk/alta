
#ifndef MOJO_SEARCH_PATH_INCLUDED
#define MOJO_SEARCH_PATH_INCLUDED

#include <string>
#include <vector>

#include <mojo/filesystem.hpp>

namespace mojo {

using std::string;
using std::vector;

/**
 * @class The SearchPath class is a helper class for getting a 
 * vector of paths contained in a search path string where a 
 * "search path string" contains absolute directory paths 
 * separated by a colon(:) or a semi-colon(;) on windows.
 */
class SearchPath {
public:

	typedef std::vector<fs::path>::iterator         iterator;
	typedef std::vector<fs::path>::const_iterator   const_iterator;

public:

	/**
	 * Create an empty SearchPath.
	 */
	SearchPath ();

	/**
	 * Initialize SearchPath from a string each path may or may not
	 * exist.
	 * 
	 * @param search_path A path string.
	 */
	SearchPath (const string& search_path);

	/**
	 * Initialize SearchPath from a vector of paths that may or may
	 * not exist.
	 *
	 * @param path A vector of paths.
	 */
	SearchPath (const vector<fs::path>& paths);

	/**
	 * Initialize SearchPath from a vector of paths that may or may
	 * not exist.
	 *
	 * @param path A vector of paths.
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
	 * the contents of an unset environment variable.
	 *
	 * @return true if there are any paths in m_paths.
	 */
	operator void* () const { return (void*)!m_dirs.empty(); }

	/**
	 *  @return a read/write iterator that points to the first
	 *  path in the SearchPath. Iteration is done in ordinary
	 *  element order.
	 */
	iterator begin () { return m_dirs.begin(); }
	
	/**
	 *  @return A read-only (constant) iterator that points to the
	 *  first path in the SearchPath.
	 */
	const_iterator begin () const { return m_dirs.begin(); }

	/**
	 *  @return A read/write iterator that points one past the last
	 *  path in the SearchPath.
	 */
	iterator end () { return m_dirs.end(); }
	
	/**
	 *  @return A read-only (constant) iterator that points one past 
	 *  the last path in the SearchPath.
	 */
	const_iterator end () const { return m_dirs.end(); }

	/**
	 * @return a search path string.
	 *
	 * The string that is returned contains the platform specific
	 * path separator. The verbosity and "explicitness" of this 
	 * method is indicitive that I don't think it should be used
	 * that often.
	 */
	const string to_string () const;

	SearchPath& operator= (const SearchPath& path);

	/**
	 * Add all the directories in path to this.
	 */
	SearchPath& operator+= (const SearchPath& path);

	/**
	 * Add another directory path to the search path.
	 */
	SearchPath& operator+= (const fs::path& directory_path);
	
	/**
	 * Concatenate another SearchPath onto this.
	 */
	SearchPath& operator+ (const SearchPath& other);
	
	/**
	 * Add another path to the search path.
	 */
	SearchPath& operator+ (const fs::path& directory_path);

	/**
	 * Add a sub-directory to each path in the search path.
	 */
	SearchPath& add_subdirectory_to_paths (const string& subdir);

	/**
	 * Add a sub-directory to each path in the search path.
	 * @see add_subdirectory_to_paths
	 */
	SearchPath& operator/ (const string& subdir);

protected:

	void add_directory (const fs::path& directory_path);

	void add_directories (const vector<fs::path>& paths);
	
	vector<fs::path> m_dirs;

};

} // namespace mojo

#endif
