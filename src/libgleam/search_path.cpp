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

#include <unistd.h>

#include <cerrno>

#include <glib.h>
#include <glib/gstdio.h>

#include <glibmm/miscutils.h>
#include <glibmm/fileutils.h>

#include <libgleam/search_path.hpp>
#include <libgleam/tokenize.hpp>
#include <libgleam/file_utils.hpp>

#include "debug.hpp"

namespace gleam {

SearchPath::SearchPath ()
{

}

SearchPath::SearchPath (const string& path)
{
	vector<string> tmp;

	if(!tokenize ( path, path_delimiter(), std::back_inserter (tmp))) {

#ifdef GLEAM_DEBUG
		LOG_GLEAM_CRITICAL;
#endif
		return;
	}

	add_readable_directories (tmp);
}

SearchPath::SearchPath (const vector<string>& paths)
{
	add_readable_directories (paths);
}

SearchPath::SearchPath (const SearchPath& other)
	: m_dirs(other.m_dirs)
{

}

bool
SearchPath::readable_directory (const string& directory_path)
{
	if (g_access (directory_path.c_str(), R_OK) == 0) {
		if (Glib::file_test(directory_path, Glib::FILE_TEST_IS_DIR)) {
			return true;
		} else {

#ifdef GLEAM_DEBUG
			LOG_GLEAM_WARNING << "Path exists but is not a directory"; 
#endif	
		}
	} else {

#ifdef GLEAM_DEBUG
		LOG_GLEAM_WARNING
			<< directory_path
			<< g_strerror(errno);
#endif	
	
	}
	return false;
}

void
SearchPath::add_readable_directory (const string& directory_path)
{
	if(readable_directory(directory_path)) {
		m_dirs.push_back(directory_path);
	}
}

void
SearchPath::add_readable_directories (const vector<string>& paths)
{
	for(vector<string>::const_iterator i = paths.begin(); i != paths.end(); ++i) {
		add_readable_directory (*i);
	}
}

const string
SearchPath::get_search_path_string () const
{
	string path;

	for (vector<string>::const_iterator i = m_dirs.begin(); i != m_dirs.end(); ++i) {
		path += (*i);
		path += path_delimiter();
	}

	path = path.substr (0, path.length() - 1); // drop final separator

#ifdef GLEAM_DEBUG_EXTRA
	LOG_GLEAM_DEBUG << path;
#endif	

	return path;
}

const SearchPath&
SearchPath::operator= (const SearchPath& path)
{
	m_dirs = path.m_dirs;
	return *this;
}

const SearchPath& 
SearchPath::operator+= (const string& directory_path)
{
	add_readable_directory (directory_path);
	return *this;
}

const SearchPath 
operator+ (const SearchPath& lhs_path, const SearchPath& rhs_path)
{
	SearchPath tmp_path(lhs_path); // does this do what I think it does.
	// concatenate paths into new SearchPath
	tmp_path.m_dirs.insert(tmp_path.m_dirs.end(), rhs_path.m_dirs.begin(), rhs_path.m_dirs.end());
	return tmp_path;
}

SearchPath&
SearchPath::add_subdirectory_to_path (const string& subdir)
{
	vector<string> tmp;
	string directory_path;

	for (vector<string>::iterator i = m_dirs.begin(); i != m_dirs.end(); ++i) {
		directory_path = Glib::build_filename (*i, subdir);
		if(readable_directory(directory_path)) {
			tmp.push_back(directory_path);
		}
	}
	m_dirs = tmp;
	return *this;
}

bool
find_file_in_path (const SearchPath& search_path,
                   const string& filename,
                   string& resulting_path)
{
	return find_file_in_search_path
		(
		 search_path.get_search_path_string(),
		 filename,
		 resulting_path
		);
}

} // namespace gleam
