#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"

#include "mojo/core/filesystem/file_utils.hpp"

#endif // MOJO_CORE_AMALGAMATED


namespace mojo {

std::size_t
find_matching_files (const vector<fs::path>& paths,
                     FileMatchFunc match_func,
                     vector<fs::path>& result)
{
	for (
		vector<fs::path>::const_iterator iter = paths.begin(),
		end = paths.end();
		iter != end;
		++iter
	    )
	{
		find_matching_files(*iter, match_func, result);
	}

	return result.size();
}

std::size_t
find_matching_files (const fs::path& dir_path,
                     FileMatchFunc match_func,
                     vector<fs::path>& result)
{
	if ( !exists( dir_path ) ) return 0;

	fs::directory_iterator end_itr; // default construction yields past-the-end

	for (
		fs::directory_iterator itr( dir_path );
		itr != end_itr;
		++itr
	    )
	{
		if ( fs::is_directory( *itr ) )
		{
			find_matching_files ( *itr, match_func, result );
		}
		else if (match_func(itr->path().filename()))
		{
			result.push_back(*itr);
		}
	}
	return result.size();
}

std::size_t
find_matching_file (const vector<fs::path>& paths,
                    const std::string& filename,
                    vector<fs::path>& result)
{
	for (
		vector<fs::path>::const_iterator iter = paths.begin(),
		end = paths.end();
		iter != end;
		++iter
	    )
	{
		find_matching_file(*iter, filename, result);
	}

	return result.size();
}

std::size_t
find_matching_file (const fs::path& dir_path,
                    const std::string& filename,
                    vector<fs::path>& result)
{
	if ( !exists( dir_path ) ) return 0;

	fs::directory_iterator end_itr; // default construction yields past-the-end

	for (
		fs::directory_iterator itr( dir_path );
		itr != end_itr;
		++itr
	    )
	{
		if ( fs::is_directory( *itr ) )
		{
			find_matching_file ( *itr, filename, result );
		}
		else if (filename == itr->path().filename())
		{
			result.push_back(*itr);
		}
	}
	return result.size();
}

bool
find_matching_file (const fs::path& dir_path,
                    const std::string& filename,
                    fs::path& result)
{
	vector<fs::path> paths;

	bool found = find_matching_file(dir_path, filename, paths);

	if (found)
	{
		result = paths.front();
	}
	return found;
}

const fs::path
get_non_existent_file_path (const fs::path& desired_file_path)
{

	if (!fs::exists( desired_file_path ))
	{
		return desired_file_path;
	}

	fs::path final_path( desired_file_path.branch_path() );

	const string filename_no_extension = fs::basename( desired_file_path );
	const string extension = fs::extension( desired_file_path );

	for (
		std::size_t num = 1;
		num < std::numeric_limits<std::size_t>::max();
		++num
	    )
	{

		std::ostringstream filename("");

		std::string basename = fs::basename( desired_file_path );

		filename << filename_no_extension << '-' << num << extension;

		final_path /= filename.str();

		if(!fs::exists( final_path )) {

			break;
		}
	}

	return final_path;
}

fs::path
tmp_writable_directory (const char* domain, const string& prefix)
{
	fs::path tmp_dir = fs::path(g_get_tmp_dir()) / domain;

	std::string dir_name;
	fs::path new_test_dir;
	do {
		std::ostringstream oss;
		oss << prefix;
		oss << g_random_int ();
		dir_name = oss.str();
		new_test_dir = tmp_dir / dir_name;
	} while (!fs::create_directories (new_test_dir));
	return new_test_dir;
}

} // namespace mojo
