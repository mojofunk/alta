#define BOOST_TEST_MODULE filesystem_paths

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

BOOST_AUTO_TEST_CASE( test_user_config_dir )
{
	const string user_config_dir = gleam::get_user_config_directory();

	BOOST_CHECK(!user_config_dir.empty());

	BOOST_TEST_MESSAGE(user_config_dir);
}

BOOST_AUTO_TEST_CASE( test_user_data_dir )
{
	const string user_data_dir = gleam::get_user_data_directory();

	BOOST_CHECK(!user_data_dir.empty());

	BOOST_TEST_MESSAGE(user_data_dir);
}

BOOST_AUTO_TEST_CASE( test_data_search_path )
{
	vector<string> data_paths = gleam::get_system_data_search_path();

	BOOST_CHECK ( !data_paths.empty() );

	log_paths ( data_paths );
}

BOOST_AUTO_TEST_CASE( test_config_search_path )
{
	vector<string> config_paths = gleam::get_system_config_search_path();

	BOOST_CHECK ( !config_paths.empty() );

	log_paths ( config_paths );
}
