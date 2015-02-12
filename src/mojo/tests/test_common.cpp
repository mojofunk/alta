#include <sstream>

#include <glib.h>

#include "gleam/utils.hpp"

#include "mojo/fs/filesystem_paths.hpp"

#include "test_common.hpp"

using namespace std;
using namespace mojo;

Searchpath
test_search_path ()
{
	Searchpath test_path(system_data_search_path());
	return Searchpath(gleam::getenv("MOJO_TEST_PATH")) + test_path;
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
