
#include <mojo/directory_names.hpp>
#include <mojo/project_directory.hpp>

#include <mojo/debug.hpp>

namespace mojo {

ProjectDirectory::ProjectDirectory (const string& project_path)
	: m_root_path(project_path)
{

}

bool
ProjectDirectory::create ()
{
	bool is_new = false;

	vector<fs::path> sub_dirs = sub_directories ();
	for (vector<fs::path>::const_iterator i = sub_dirs.begin(); i != sub_dirs.end(); ++i)
	{
		try
		{
			if(fs::create_directories(*i)) {

#ifdef MOJO_DEBUG_EXTRA
				LOG_MOJO_DEBUG
					<< "Created Project directory at path"
					<< (*i).string ();
#endif

				is_new = true;
			}
		}
		catch (...)
		{

			// catch exception, log and rethrow

#ifdef MOJO_DEBUG
			LOG_MOJO_WARNING
				<< "Cannot create project directory at path"
				<< (*i).string ();
#endif
			throw;
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

#ifdef MOJO_DEBUG
			LOG_MOJO_WARNING
				<< "Project subdirectory does not exist at path"
				<< (*i).string();
#endif

			return false;
		}
	}
	return true;
}

const fs::path
ProjectDirectory::audiofiles_path () const
{
	fs::path l_audiofiles_path(m_root_path);

	l_audiofiles_path /= audiofiles_dir_name;

	return l_audiofiles_path;
}

const fs::path
ProjectDirectory::peak_path () const
{
	return fs::path(m_root_path) /= peak_dir_name;
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
