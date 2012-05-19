
#define BOOST_TEST_MODULE mojo_filesystem_paths

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <mojo/mojo-internal.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

void
test_path (const fs::path& p)
{
	BOOST_REQUIRE(!p.empty());
	BOOST_TEST_MESSAGE(p);
}

void
test_search_path (const SearchPath& sp)
{
	for_each (sp.begin(), sp.end(), test_path);
}

BOOST_AUTO_TEST_CASE( user_config_dir_test )
{
	test_path (user_config_directory ());
}

BOOST_AUTO_TEST_CASE( mojo_search_path_test )
{
	test_search_path (mojo_search_path ());
}

BOOST_AUTO_TEST_CASE( system_config_search_path_test )
{
	test_search_path (system_config_search_path ());
}

BOOST_AUTO_TEST_CASE( system_data_search_path_test )
{
	test_search_path (system_data_search_path ());
}

BOOST_AUTO_TEST_CASE( module_search_path_test )
{
	test_search_path (module_search_path ());
}
