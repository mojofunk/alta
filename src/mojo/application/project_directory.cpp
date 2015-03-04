
#ifndef MOJO_APPLICATION_AMALGAMATED
#include "directory_names.hpp"
#include "project_directory.hpp"
#endif

namespace mojo {

ProjectDirectory::ProjectDirectory (const fs::path& project_path)
	:
		m_root_path(project_path)
{

}

bool
ProjectDirectory::create ()
{
	bool is_new = false;

	vector<fs::path> sub_dirs = sub_directories ();
	for (vector<fs::path>::const_iterator i = sub_dirs.begin(); i != sub_dirs.end(); ++i)
	{
		if(fs::create_directories(*i)) {
			is_new = true;
		}
	}

	return is_new;
}

bool
ProjectDirectory::is_valid () const
{
	if (!fs::is_directory (m_root_path)) return false;

	vector<fs::path> sub_dirs = sub_directories ();

	for (vector<fs::path>::iterator i = sub_dirs.begin(); i != sub_dirs.end(); ++i) {
		if (!fs::is_directory (*i)) {
			return false;
		}
	}
	return true;
}

const fs::path
ProjectDirectory::audiofiles_path () const
{
	return m_root_path / audiofiles_dir_name;
}

const fs::path
ProjectDirectory::peak_path () const
{
	return m_root_path / peak_dir_name;
}

const vector<fs::path>
ProjectDirectory::sub_directories () const
{
	vector<fs::path> tmp_paths;

	tmp_paths.push_back ( audiofiles_path () );
	tmp_paths.push_back ( peak_path () );

	return tmp_paths;
}

} // namespace mojo