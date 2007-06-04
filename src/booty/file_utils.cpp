
#include <booty/file_utils.hpp>

namespace booty {

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

} // namespace booty
