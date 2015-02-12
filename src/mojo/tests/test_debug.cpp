#define BOOST_TEST_MODULE mojo_debug

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "mojo/core/debug.hpp"

using namespace boost::unit_test;
using namespace std;

MOJO_DEBUG_DOMAIN( TEST_DOMAIN_ONE );
MOJO_DEBUG_DOMAIN( TEST_DOMAIN_TWO );

BOOST_AUTO_TEST_CASE( debug_simple_test )
{
	MOJO_DEBUG_MSG(TEST_DOMAIN_ONE, "First Debug Message");

	BOOST_CHECK(!mojo::debug::get_enabled(TEST_DOMAIN_ONE));
	mojo::debug::set_enabled(TEST_DOMAIN_ONE, true);
	BOOST_CHECK(mojo::debug::get_enabled(TEST_DOMAIN_ONE));
	mojo::debug::set_enabled(TEST_DOMAIN_ONE, false);
	BOOST_CHECK(!mojo::debug::get_enabled(TEST_DOMAIN_ONE));
	mojo::debug::set_enabled(TEST_DOMAIN_ONE, true);

	MOJO_DEBUG_MSG(TEST_DOMAIN_ONE, "Second Debug Message");
	MOJO_DEBUG_MSG(TEST_DOMAIN_TWO, "A Debug Message");

	mojo::debug::set_enabled(TEST_DOMAIN_TWO, true);

	MOJO_DEBUG_MSG(TEST_DOMAIN_TWO, "A Debug Message");

}

BOOST_AUTO_TEST_CASE( debug_domain_name_test )
{
	std::vector<std::string> domain_names;
	mojo::debug::get_registry().get_domains(domain_names);
	BOOST_TEST_MESSAGE(domain_names.size());

	for (auto& x : domain_names)
	{
		BOOST_TEST_MESSAGE(x);
	}
}
