#include <algorithm>

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <libgleam/filesystem_paths.hpp>

using namespace boost::unit_test;
using namespace std;

void
log_paths(const vector<string>& paths)
{
	for (vector<string>::const_iterator i = paths.begin(); i != paths.end(); ++i)
	    {
		BOOST_MESSAGE( *i );
	    }
}

void
test_data_search_path()
{
	vector<string> data_paths = gleam::get_system_data_search_path();

	BOOST_CHECK ( !data_paths.empty() );

	log_paths ( data_paths );

}

void
test_config_search_path()
{
	vector<string> config_paths = gleam::get_system_config_search_path();

	BOOST_CHECK ( !config_paths.empty() );

	log_paths ( config_paths );

}

test_suite*
init_unit_test_suite( int argc, char* argv[] )
{
	test_suite* test = BOOST_TEST_SUITE( "Filesystem Paths" );

	test->add( BOOST_TEST_CASE( &test_data_search_path ) );
	test->add( BOOST_TEST_CASE( &test_config_search_path ) );

	return test;
}
