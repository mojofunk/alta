
#define BOOST_TEST_MODULE mojo_file_utils

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "mojo/core/string/compose.hpp"

#include "mojo/core/filesystem/filesystem.hpp"
#include "mojo/core/filesystem/file_utils.hpp"

#include "mojo/application/project_directory.hpp"

#include "test_common.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE(test_get_non_existant_file_path)
{
	fs::path project_path;

	BOOST_CHECK(find_directory_in_test_path("projects", project_path));

	project_path = project_path / "motronic";

	fs::path project_audiofile_dir =
	    ProjectDirectory(project_path).audiofiles_path();

	fs::path path = project_audiofile_dir / "notify.wav";

	BOOST_CHECK(fs::exists(path));

	const fs::path new_path(get_non_existent_file_path(path));

	BOOST_CHECK(path != new_path);

	BOOST_CHECK(!fs::exists(new_path));

	const fs::path expected_path(project_audiofile_dir / "notify-1.wav");

	BOOST_CHECK_EQUAL(new_path, expected_path);
}

BOOST_AUTO_TEST_CASE(test_tmp_writable_directory)
{
	std::set<fs::path> m_tmp_dirs;

	const int num_dirs = 1000;

	for (int i = 0; i < num_dirs; ++i) {
		m_tmp_dirs.insert(tmp_writable_directory("mojo-test", "tmp"));
	}

	BOOST_CHECK(m_tmp_dirs.size() == num_dirs);

	for (auto const& path : m_tmp_dirs) {
		BOOST_CHECK_NO_THROW(fs::remove(path) == 1);
	}
}

BOOST_AUTO_TEST_CASE(test_copy_i18n_files)
{
	fs::path i18n_dir_path;

	BOOST_CHECK(find_directory_in_test_path("i18n_test", i18n_dir_path));

	fs::path top_output_dir = tmp_writable_directory("mojo-test", "i18n_test");

	fs::path output_dir = top_output_dir / "i18n_copy";

	BOOST_CHECK(!exists(output_dir));

	BOOST_CHECK_NO_THROW(fs::copy_directory(i18n_dir_path, output_dir));

	BOOST_CHECK_NO_THROW(fs::remove_all(output_dir));

	BOOST_CHECK_NO_THROW(fs::remove(top_output_dir));
}
