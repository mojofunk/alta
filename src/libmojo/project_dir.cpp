
#include <libgleam/file_utils.hpp>

using namespace gleam;

#include <libmojo/project_dir.hpp>

#include "debug.hpp"

namespace mojo {

const char* const ProjectDir::sound_dir_name = "sounds";    

const char* const ProjectDir::peak_dir_name = "peaks";

ProjectDir::ProjectDir (const string& project_path)
	: m_path(project_path)
{
	if(!directories_exist()) {

	//	throw invalid_project_exception ();
	}
}

ProjectDir::ProjectDir (const string& project_path,
                        const string& project_name)
	: m_path(project_path / project_name)
{
	if(!create_subdirectories()) {
//		throw failed_constructor ();
	}
}

bool
ProjectDir::create_subdirectories () const
{
	vector<string> sub_dirs = sub_directories ();

	for(vector<string>::const_iterator i = sub_dirs.begin(); i != sub_dirs.end(); ++i) {
		if (!create_directory (*i)) {

#ifdef MOJO_DEBUG
			LOG_MOJO_WARNING
				<< "Cannot create project subdirectory at path"
				<< (*i);
#endif

			return false;	
		}
	}

	return true;
}

bool
ProjectDir::directories_exist () const
{
	vector<string> sub_dirs = sub_directories ();

	if (!directory_exists (m_path)) {

#ifdef MOJO_DEBUG
		LOG_MOJO_WARNING
			<< "project directory does not exist at path"
			<< m_path;
#endif

		return false;
	}

	for(vector<string>::iterator i = sub_dirs.begin(); i != sub_dirs.end(); ++i) {
		if (!directory_exists (*i)) {

#ifdef MOJO_DEBUG
			LOG_MOJO_WARNING
				<< "project subdirectory does not exist at path"
				<< *i;
#endif

			return false;
		}
	}
	return true;
}

const string
ProjectDir::sound_dir () const
{
	return m_path / sound_dir_name;
}

const string
ProjectDir::peak_dir () const
{
	return m_path / peak_dir_name;
}

const vector<string>
ProjectDir::sub_directories () const
{
	vector<string> tmp_dirs; 

	tmp_dirs.push_back ( sound_dir () );
	tmp_dirs.push_back ( peak_dir () );

	return tmp_dirs;
}

} // namespace MOJO
