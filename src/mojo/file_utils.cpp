
#include <sstream>

#include <mojo/filesystem.hpp>
#include <mojo/file_utils.hpp>

#include <mojo/debug.hpp>

namespace mojo {

const fs::path
get_non_existent_file_path (const fs::path& desired_file_path)
{

	if (!fs::exists (desired_file_path))
	{
		return desired_file_path;
	}

	fs::path filepath(desired_file_path.branch_path ());

	for (
		std::size_t num = 1;
		num < std::numeric_limits<std::size_t>::max();
		++num
	    )
	{

		std::ostringstream filename("");

		std::string basename = fs::basename (desired_file_path);

		filename << basename << '-' << num << fs::extension(desired_file_path);

		filepath /= filename.str();

#ifdef MOJO_DEBUG_EXTRA
		LOG_MOJO_DEBUG << filepath.string ();
#endif

		if(!fs::exists(filepath)) {

			break;
		}
	}
	
	return filepath;
}

} // namespace mojo
