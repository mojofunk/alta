
#define BOOST_TEST_MODULE mojo_project_directory

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <mojo/project_directory.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE( test_project_directory )
{
	// XXX not absolute...
	ProjectDirectory pdir("./share/projects/motronic");

	bool is_new = false;
	
	BOOST_CHECK_NO_THROW(is_new = pdir.create ());

	BOOST_CHECK(!is_new);

	BOOST_CHECK(is_directory (pdir.root_path ()));
	BOOST_CHECK(is_directory (pdir.audiofiles_path ()));
	BOOST_CHECK(is_directory (pdir.peak_path ()));

	BOOST_CHECK(pdir.is_valid ());
}
