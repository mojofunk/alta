#define BOOST_TEST_MODULE mojo_log

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "mojo/core/logging/log.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE(log_simple_test) { mojo::log("NONE", "A Message"); }
