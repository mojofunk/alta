
#define BOOST_TEST_MODULE mojo_filesystem_paths

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <mojo/filesystem_paths.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

void
test_search_path (const SearchPath& sp)
{
	for (SearchPath::const_iterator i = sp.begin();
			i != sp.end(); ++i)
	{
		BOOST_REQUIRE(!i->empty());
		BOOST_TEST_MESSAGE(*i);
	}
}

BOOST_AUTO_TEST_CASE( user_config_dir_test )
{
	fs::path user_dir = user_config_directory();

	BOOST_REQUIRE(!user_dir.empty());
	BOOST_TEST_MESSAGE(user_dir);
}

BOOST_AUTO_TEST_CASE( mojo_search_path_test )
{
	test_search_path (mojo_search_path ());
}

BOOST_AUTO_TEST_CASE( system_config_search_path_test )
{
	test_search_path (system_config_search_path ());
}

BOOST_AUTO_TEST_CASE( plugin_search_path_test )
{
	test_search_path (plugin_search_path ());
}
