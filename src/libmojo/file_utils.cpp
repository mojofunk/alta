
#include <boost/filesystem/operations.hpp>

using namespace boost::filesystem;

#include <libmojo/file_utils.hpp>

namespace mojo {

vector<string>
paths_to_strings(const vector<path>& paths)
{

	return vector<string>();
}

vector<path>
strings_to_paths(const vector<string>& string_paths)
{

	return vector<path>();
}

std::size_t
find_matching_files (const vector<path>& paths,
                     FileMatchFunc match_func,
                     vector<path>& result)
{
	std::size_t count = 0;

	for ( vector<path>::const_iterator iter = paths.begin(),
			end = paths.end();
			iter != end;
			++iter )
	{
		count += find_matching_files(*iter, match_func, result);
	}

	return count;
}

std::size_t
find_matching_files (const path& dir_path, 
                     FileMatchFunc match_func,
                     vector<path>& result)
{
	std::size_t count = 0;

	if ( !exists( dir_path ) ) return 0;

	directory_iterator end_itr; // default construction yields past-the-end
	for ( directory_iterator itr( dir_path );
			itr != end_itr;
			++itr )
	{
		if ( is_directory( *itr ) )
		{
			count += find_matching_files ( *itr, match_func, result );
		}
		else if (match_func(itr->leaf()))
		{
			result.push_back(*itr);
			++count;
		}
	}
	return count;
}

} // namespace mojo
