
#ifndef MOJO_PROJECT_DIRECTORY_INCLUDED
#define MOJO_PROJECT_DIRECTORY_INCLUDED

#include <string>
#include <vector>

#include <mojo/filesystem.hpp>

namespace mojo {

using std::string;
using std::vector;

class ProjectDirectory
{
public:
	/**
	 * @param project_path An absolute path to a project directory.
	 */
	ProjectDirectory (const string& project_path);

	/**
	 * @return the absolute path to the root directory of the project
	 */
	const fs::path root_path() const { return m_root_path; }

	/**
	 * @return the absolute path to the directory in which 
	 * the project stores audio files.
	 */
	const fs::path audiofiles_path () const;

	/**
	 * @return The absolute path to the directory in which all
	 * peak files are stored for a project.
	 */
	const fs::path peak_path () const;

	/**
	 * @return true if project directory and all the required 
	 * subdirectories exist.
	 */
	bool is_valid () const;

	/**
	 * Create the project directory and all the subdirectories.
	 *
	 * @throw boost::filesystem::filesystem_error if the directories were
	 * not able to be created.
	 *
	 * @return true If a new project directory was created, otherwise
	 * (if it already existed) false.
	 *
	 * @post is_valid ()
	 */
	bool create ();

protected:

	/**
	 * @return a vector containing the fullpath of all subdirectories.
	 */
	const vector<fs::path> sub_directories () const;

	/// The path to the root of the project directory.
	const fs::path m_root_path;
};

} // namespace mojo

#endif
