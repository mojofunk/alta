#include <sstream>

#include <glib.h>

#include "mojo/core/system/utils.hpp"
#include "mojo/core/filesystem/filesystem_paths.hpp"

#include "test_common.hpp"

using namespace std;
using namespace mojo;

Searchpath
test_search_path ()
{
	Searchpath test_path(system_data_search_path());
	return Searchpath(mojo::getenv("MOJO_TEST_PATH")) + test_path;
}

bool
find_file_in_test_path (const std::string& filename, fs::path& result)
{
	// don't tests for is_regular_file as that fails for modules/executables
	for (auto const& path : test_search_path()) {
		if (exists (path / filename)) {
			result = path / filename;
			return true;
		}
	}
	return false;
}

bool
find_directory_in_test_path (const std::string& dirname, fs::path& result)
{

	for (auto const& path : test_search_path()) {
		if (is_directory (path / dirname)) {
			result = path / dirname;
			return true;
		}
	}
	return false;
}

fs::path
new_test_output_dir ()
{
	fs::path tmp_dir(g_get_tmp_dir());
	tmp_dir /= "mojo_test";
	string dir_name;
	do {
		ostringstream oss;
		oss << g_random_int ();
		dir_name = oss.str();
	} while (!fs::create_directories (tmp_dir / dir_name));
	return tmp_dir / dir_name;
}
