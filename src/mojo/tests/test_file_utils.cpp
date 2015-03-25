
#define BOOST_TEST_MODULE mojo_file_utils

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "mojo/core/filesystem/filesystem.hpp"
#include "mojo/core/filesystem/file_utils.hpp"

#include "mojo/application/project_directory.hpp"

#include "test_common.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE( test_get_non_existant_file_path )
{
	fs::path project_path;

	BOOST_CHECK(find_directory_in_test_path ("projects", project_path));

	project_path = project_path / "motronic";

	fs::path project_audiofile_dir = ProjectDirectory(project_path).audiofiles_path();

	fs::path path = project_audiofile_dir / "notify.wav";

	BOOST_CHECK(fs::exists (path));

	const fs::path new_path(get_non_existent_file_path (path));

	BOOST_CHECK(path != new_path);

	BOOST_CHECK(!fs::exists (new_path));

	const fs::path expected_path(project_audiofile_dir / "notify-1.wav");

	BOOST_CHECK_EQUAL(new_path, expected_path);
}
