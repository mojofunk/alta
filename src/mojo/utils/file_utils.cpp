#include <sstream>
#include <limits>

#include "file_utils.hpp"

namespace mojo {

std::size_t
find_matching_files (const vector<fs::path>& paths,
                     FileMatchFunc match_func,
                     vector<fs::path>& result)
{
	for ( vector<fs::path>::const_iterator iter = paths.begin(),
			end = paths.end();
			iter != end;
			++iter )
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

	for ( fs::directory_iterator itr( dir_path );
			itr != end_itr;
			++itr )
	{
		if ( fs::is_directory( *itr ) )
		{
			find_matching_files ( *itr, match_func, result );
		}
		else if (match_func(itr->leaf()))
		{
			result.push_back(*itr);
		}
	}
	return result.size();
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

} // namespace mojo
