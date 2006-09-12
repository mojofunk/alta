/*
   Copyright (C) 2006 Tim Mayberry

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA  02110-1301, USA.
*/

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include <libmojo/project_dir.h>

//#include "debug.h"

namespace mojo {

const char* const ProjectDir::sound_dir_name = "sounds";    

const char* const ProjectDir::peak_dir_name = "peaks";

ProjectDir::ProjectDir (const string& project_path)
	: m_path(project_path)
{
	if(!directories_exist()) {

		// throw a meaningful exception containing the log string.
#ifdef MOJO_DEBUG
		LOG_MOJO_WARNING
			<< m_path
			<< "is not a project directory";
#endif	

		throw failed_constructor ();
	}
}

ProjectDir::ProjectDir (const string& project_path,
		const string& project_name)
	: m_path(Glib::build_filename (project_path, project_name))
{
	if (!PBD::create_directory(m_path)) {

#ifdef MOJO_DEBUG
		LOG_MOJO_WARNING
			<< "Cannot create project directory at path"
			<< m_path;
#endif

		throw failed_constructor ();
	}

	if(!create_subdirectories()) {
		throw failed_constructor ();
	}
}

bool
ProjectDir::create_subdirectories () const
{
	vector<string> sub_dirs = sub_directories ();

	for(vector<string>::const_iterator i = sub_dirs.begin(); i != sub_dirs.end(); ++i) {
		if (!PBD::create_directory (*i)) {

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

	if (!PBD::directory_exists (m_path)) {

#ifdef MOJO_DEBUG
		LOG_MOJO_WARNING
			<< "project directory does not exist at path"
			<< m_path;
#endif

		return false;
	}

	for(vector<string>::iterator i = sub_dirs.begin(); i != sub_dirs.end(); ++i) {
		if (!PBD::directory_exists (m_path)) {

#ifdef MOJO_DEBUG
			LOG_MOJO_WARNING
				<< "project subdirectory does not exist at path"
				<< m_path;
#endif

			return false;
		}
	}
	return true;
}

const string
ProjectDir::sound_dir () const
{
	return Glib::build_filename (m_path, sound_dir_name);
}

const string
ProjectDir::peak_dir () const
{
	return Glib::build_filename (m_path, peak_dir_name);
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
