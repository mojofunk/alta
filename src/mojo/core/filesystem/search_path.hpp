#ifndef MOJO_SEARCH_PATH_H
#define MOJO_SEARCH_PATH_H

namespace mojo {

/**
 * @class The Searchpath class is a helper class for getting a
 * vector of paths contained in a search path string where a
 * "search path string" contains absolute directory paths
 * separated by a colon(:) or a semi-colon(;) on windows.
 */
class Searchpath {
public:
	typedef paths_t::iterator iterator;
	typedef paths_t::const_iterator const_iterator;

public:
	/**
	 * Create an empty Searchpath.
	 */
	Searchpath();

	/**
	 * Initialize Searchpath from a string each path may or may not
	 * exist.
	 *
	 * @param search_path A path string.
	 */
	Searchpath(const std::string& search_path);

	/**
	 * Initialize Searchpath from a single fs::path
	 *
	 * @param search_path A path string.
	 */
	Searchpath(const fs::path& search_path);

	/**
	 * Initialize Searchpath from a vector of paths that may or may
	 * not exist.
	 *
	 * @param path A vector of paths.
	 */
	Searchpath(const paths_t& paths);

	/**
	 * Initialize Searchpath from a vector of paths that may or may
	 * not exist.
	 *
	 * @param path A vector of paths.
	 */
	Searchpath(const std::vector<std::string>& paths);

	/**
	 * The copy constructor does what you would expect and copies the
	 * vector of paths contained by the Searchpath.
	 */
	Searchpath(const Searchpath& search_path);

	/**
	 * Indicate whether there are any directories in m_dirs, if Searchpath
	 * is initialized with an empty string as the result of for instance
	 * the contents of an unset environment variable.
	 *
	 * @return true if there are any paths in m_paths.
	 */
	operator void*() const { return (void*)!m_dirs.empty(); }

	/**
	 *  @return a read/write iterator that points to the first
	 *  path in the Searchpath. Iteration is done in ordinary
	 *  element order.
	 */
	iterator begin() { return m_dirs.begin(); }

	/**
	 *  @return A read-only (constant) iterator that points to the
	 *  first path in the Searchpath.
	 */
	const_iterator begin() const { return m_dirs.begin(); }

	/**
	 *  @return A read/write iterator that points one past the last
	 *  path in the Searchpath.
	 */
	iterator end() { return m_dirs.end(); }

	/**
	 *  @return A read-only (constant) iterator that points one past
	 *  the last path in the Searchpath.
	 */
	const_iterator end() const { return m_dirs.end(); }

	/**
	 * @return a search path string.
	 *
	 * The string that is returned contains the platform specific
	 * path separator. The verbosity and "explicitness" of this
	 * method is indicitive that I don't think it should be used
	 * that often.
	 */
	const std::string to_string() const;

	/**
	 * @return The vector of directory paths in the search path
	 */
	paths_t get_paths() const { return m_dirs; }

	Searchpath& operator=(const Searchpath& path);

	/**
	 * Add all the directories in path to this.
	 */
	Searchpath& operator+=(const Searchpath& path);

	/**
	 * Add another directory path to the search path.
	 */
	Searchpath& operator+=(const fs::path& directory_path);

	/**
	 * Concatenate another Searchpath onto this.
	 */
	const Searchpath operator+(const Searchpath& other);

	/**
	 * Add another path to the search path.
	 */
	const Searchpath operator+(const fs::path& directory_path);

	/**
	 * Add a sub-directory to each path in the search path.
	 */
	Searchpath& add_subdirectory_to_paths(const std::string& subdir);

	/**
	 * Add a sub-directory to each path in the search path.
	 * @see add_subdirectory_to_paths
	 */
	Searchpath& operator/(const std::string& subdir);

protected:
	void add_directory(const fs::path& directory_path);

	paths_t m_dirs;
};

} // namespace mojo

#endif // MOJO_SEARCH_PATH_H
