
#if HAVE_UNISTD_H
#include <unistd.h>
#else
#include <io.h> // non-mingw
#endif

#include <algorithm>
#include <cerrno>

#include <glib.h>
#include <glib/gstdio.h>

#include <glibmm/fileutils.h>
#include <glibmm/miscutils.h>
#include <glibmm/pattern.h>

#include <libgleam/file_utils.hpp>
#include <libgleam/tokenize.hpp>

#include "debug.hpp"

namespace {
	const char path_delim = G_SEARCHPATH_SEPARATOR;
	const int default_permission_mode = 0775;
}

namespace gleam {
	
const string
path_delimiter()	
{
	return &path_delim;
}

const string
operator/ (const string& base_path, const string& path_element)
{
	return Glib::build_filename(base_path, path_element);
}

void
get_files_in_directory (const string& directory, vector<string>& result)
{
	try
	{
		Glib::Dir dir(directory);
		std::copy(dir.begin(), dir.end(), std::back_inserter(result));
	}
	catch (Glib::FileError& err)
	{

#ifdef GLEAM_DEBUG		
		LOG_GLEAM_WARNING << err.what();
#endif

	}
}

void
find_matching_files (const vector<string>& paths,
                     const Glib::PatternSpec& pattern,
                     vector<string>& result)
{
	vector<string> tmp_files;

	for (vector<string>::const_iterator path_iter = paths.begin();
			path_iter != paths.end();
			++path_iter)
	{
		get_files_in_directory (*path_iter, tmp_files);
		
		for (vector<string>::iterator file_iter = tmp_files.begin();
				file_iter != tmp_files.end();
				++file_iter)
		{
			
			if(!pattern.match(*file_iter)) continue;

			string full_path = Glib::build_filename(*path_iter, *file_iter);

			result.push_back(full_path);

#ifdef GLEAM_DEBUG_EXTRA
			LOG_GLEAM_DEBUG
				<< "Found file"
				<< full_path;
#endif

		}

		tmp_files.clear();
	}
}

void
find_matching_files_in_search_path (const string& search_path,
                                    const Glib::PatternSpec& pattern,
                                    vector<string>& result)
{
	vector<string> dirs;
	if(!tokenize(search_path, path_delimiter(), std::back_inserter(dirs))) {

#ifdef GLEAM_DEBUG
		LOG_GLEAM_CRITICAL ;
#endif

		return;
	}
	find_matching_files (dirs, pattern, result);    
}

bool
find_file_in_search_path(const string& search_path,
                         const string& filename,
                         string& result)
{
	vector<string> tmp;
	Glib::PatternSpec tmp_pattern(filename);

	find_matching_files_in_search_path(search_path, tmp_pattern, tmp);

	if(tmp.size() != 1) {

#ifdef GLEAM_DEBUG
		LOG_GLEAM_WARNING
			<< "Found more than a single file in search path"
			<< filename;
#endif

		return false;
	}

	result = tmp.front();

	return true;
}

bool
file_exists (const string& path)
{
	return (Glib::file_test (path, Glib::FILE_TEST_EXISTS) &&
			Glib::file_test (path, Glib::FILE_TEST_IS_REGULAR));

}

bool
file_is_writable (const string& path)
{
	if(!file_exists (path))	return false;
	
	if(g_access(path.c_str(), W_OK) != 0)
	{

#ifdef GLEAM_DEBUG
		LOG_GLEAM_WARNING << path << g_strerror(errno);
#endif		

		return false;
	}
	return true;
}

bool
file_is_empty (const string& path)
{
//	return (file_size(path) == 0);

	struct stat	stat_buf;

	if(g_stat (path.c_str(), &stat_buf) != 0)
	{

#ifdef GLEAM_DEBUG
		LOG_GLEAM_WARNING << path << g_strerror(errno);
#endif
		return true;
	}

	return (stat_buf.st_size == 0);
}

bool
access_file (const string& path, int mode)
{
	if(g_access(path.c_str(), mode) != 0)
	{

#ifdef GLEAM_DEBUG
		LOG_GLEAM_WARNING
			<< path
			<< mode
			<< g_strerror(errno);
#endif

		return false;
	}
	return true;
}

bool
rename_file(const string& old_path, const string& new_path)
{

	if (g_rename(old_path.c_str(), new_path.c_str()) != 0)
	{

#ifdef GLEAM_DEBUG
		LOG_GLEAM_WARNING
			<< old_path
			<< new_path
			<< g_strerror(errno);
#endif

		return false;
	}
	return true;
}

bool
directory_exists (const string& path)
{
	return (Glib::file_test (path, Glib::FILE_TEST_EXISTS) &&
			Glib::file_test (path, Glib::FILE_TEST_IS_DIR));
}

/*
 * XXX according to this :
 * http://developer.gnome.org/doc/API/2.0/glib/glib-File-Utilities.html#g-access
 * we will need to do something platform specific for Windows
 */
bool
directory_is_writable (const string& path)
{
	if(!directory_exists(path)) return false;
	
	if(g_access(path.c_str(), W_OK) != 0)
	{

#ifdef GLEAM_DEBUG
		LOG_GLEAM_WARNING << g_strerror(errno);
#endif		

		return false;
	}
	return true;
}

bool
create_directory (const string& path)
{
	if ((g_mkdir_with_parents (path.c_str(), default_permission_mode) != 0))
	{

#ifdef GLEAM_DEBUG
		LOG_GLEAM_WARNING
			<< "Cannot create directory at path" 
			<< path
			<< g_strerror(errno);
#endif

		return false;	
	}

	return true;
}

bool
file_is_more_recently_modified (const string& newer_file,
                                const string& older_file)
{
	struct stat	stat_buf_newer;
	struct stat	stat_buf_older;

	if(g_stat (newer_file.c_str(), &stat_buf_newer) != 0)
	{

#ifdef GLEAM_DEBUG
		LOG_GLEAM_WARNING
			<< newer_file
			<< g_strerror(errno);
#endif

		return true;
	}

	if(g_stat (older_file.c_str(), &stat_buf_older) != 0)
	{

#ifdef GLEAM_DEBUG
		LOG_GLEAM_WARNING
			<< older_file
			<< g_strerror(errno);
#endif

		return true;
	}

	return (stat_buf_newer.st_mtime > stat_buf_older.st_mtime);
}

} // namespace gleam
