#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_cppformat
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "mojo-core.hpp"

#include <iostream>

BOOST_AUTO_TEST_CASE(basic_cppformat_test)
{
	// print to stdout
	fmt::print("stdout: {}: {}:\n", __LINE__, __FILE__);

	// print to stdout
	fmt::print(stderr, "stderr: {}: {}:\n", __LINE__, __FILE__);

	std::cout << fmt::format("std::cout {}: {}:", __LINE__, __FILE__) << std::endl;

	std::cerr << fmt::format("std::cerr {}: {}:", __LINE__, __FILE__) << std::endl;
}
