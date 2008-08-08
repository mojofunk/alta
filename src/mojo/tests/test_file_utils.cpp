
#define BOOST_TEST_MODULE mojo_file_utils

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <mojo/utils/file_utils.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE( test_get_non_existant_file_path )
{
	const fs::path path("share/projects/motronic/audiofiles/notify.wav"); 

	BOOST_CHECK(fs::exists (path));

	const fs::path new_path(get_non_existent_file_path (path));

	BOOST_CHECK(path != new_path);

	BOOST_CHECK(!fs::exists (new_path));

	const fs::path expected_path("share/projects/motronic/audiofiles/notify-1.wav");

	BOOST_CHECK_EQUAL(new_path, expected_path);
}
