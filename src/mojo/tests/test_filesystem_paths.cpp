
#define BOOST_TEST_MODULE mojo_filesystem_paths

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <mojo/filesystem_paths.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE( user_config_dir_test )
{
	fs::path user_dir = user_config_directory();

	BOOST_REQUIRE(!user_dir.empty());
	BOOST_TEST_MESSAGE(user_dir);
}

BOOST_AUTO_TEST_CASE( mojo_search_path_test )
{
	SearchPath mojo = mojo_search_path();

	for (SearchPath::iterator i = mojo.begin();
			i != mojo.end(); ++i)
	{
		BOOST_REQUIRE(!i->empty());
		BOOST_TEST_MESSAGE(*i);
	}
}
