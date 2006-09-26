
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

SearchPath&
SearchPath::operator= (const SearchPath& path)
{
	m_dirs = path.m_dirs;
	return *this;
}

SearchPath& 
SearchPath::operator+= (const SearchPath& spath)
{
	m_dirs.insert(m_dirs.end(), spath.m_dirs.begin(), spath.m_dirs.end());
	return *this;
}

SearchPath& 
SearchPath::operator+= (const string& directory_path)
{
	add_readable_directory (directory_path);
	return *this;
}

SearchPath& 
SearchPath::operator+ (const string& directory_path)
{
	add_readable_directory (directory_path);
	return *this;
}

SearchPath& 
SearchPath::operator+ (const SearchPath& spath)
{
	// concatenate paths into new SearchPath
	m_dirs.insert(m_dirs.end(), spath.m_dirs.begin(), spath.m_dirs.end());
	return *this;
}

SearchPath&
SearchPath::add_subdirectory_to_paths (const string& subdir)
{
	vector<string> tmp;
	string directory_path;

	for (vector<string>::iterator i = m_dirs.begin(); i != m_dirs.end(); ++i)
	{
		directory_path = Glib::build_filename (*i, subdir);

		if(readable_directory(directory_path))
		{
			tmp.push_back(directory_path);
		}
	}

	m_dirs = tmp;
	return *this;
}
	
SearchPath&
SearchPath::operator/ (const string& subdir)
{
	return add_subdirectory_to_paths (subdir);
}

} // namespace gleam
