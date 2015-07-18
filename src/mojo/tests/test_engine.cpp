#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_archive_modules
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "mojo/engine/engine.hpp"

using namespace boost::unit_test;
using namespace mojo;

BOOST_AUTO_TEST_CASE(test_engine_basic)
{
	Engine engine;
}
