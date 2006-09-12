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

#ifndef MOJO_PROJECT_DIR_INCLUDED
#define MOJO_PROJECT_DIR_INCLUDED

#include <string>
#include <vector>

namespace mojo {

using std::string;
using std::vector;

struct ProjectDir {

	/**
	  Create a representation of an existing project directory, this will
	  test to ensure that the project directory and all subdirectories exist,
	  a PBD::failed_constructor exception will be thrown if an error occurs.
	  \param project_path An absolute path to a project directory.
	  */
	ProjectDir (const string& project_path);

	/**
	  Create a new project directory, project_name will be used as the name
	  of the project directory to be created at path.
	  \param path directory in which to create project directory.
	  \param project_name name to use for project directory.
	  */
	ProjectDir (const string& path, const string& project_name);

	/**
	  \return the absolute path to the project directory.
	  */
	operator const string& () const { return m_path; }
	
	/**
	  \return the absolute path to the project directory.
	  */
	const string path() const { return m_path; }

	const string sound_dir () const;
	const string peak_dir () const;
	
protected:

	/**
	  Create subdirectories with the project directory
	  \return true If subdirectories were able to be created.
	  */
	bool create_subdirectories () const;
	
	/**
	  \return a vector containing the fullpath of
	  all subdirectories.
	  */
	const vector<string> sub_directories () const;
	
	/**
	  \return true if the project directory and all of the 
	  subdirectories exist.
	  */
	bool directories_exist () const;
	
	static const char* const sound_dir_name;
	static const char* const peak_dir_name;

	const string m_path;
};

} // namespace mojo

#endif // MOJO_PROJECT_DIR_INCLUDED

