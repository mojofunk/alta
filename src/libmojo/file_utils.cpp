#include <sstream>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include <libmojo/file_utils.hpp>

#include "debug.hpp"

using namespace std;

namespace mojo {

using namespace boost::filesystem;

const string
get_unique_filename (const string& dir,
                     const string& name,
                     const string& ext)
{

	if(!is_directory (dir))
	{

#ifdef MOJO_DEBUG

		LOG_MOJO_CRITICAL;

#endif

		// throw exception ??
		return string();
	}

	path filepath;

	for (
			std::size_t num = 1;
			num < std::numeric_limits<std::size_t>::max();
			++num
		)
	{
		std::ostringstream filename(name);

		path tmppath(dir);

		filename << name << '-' << num << ext;

		tmppath /= filename.str();

#ifdef MOJO_DEBUG_EXTRA

			LOG_MOJO_DEBUG << filepath.native_file_string();

#endif

		if(!exists(tmppath)) {

			filepath = tmppath;

			break;
		}
	}
	
	return filepath.native_file_string();
}

} // namespace mojo
