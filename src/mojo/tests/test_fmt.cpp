#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_fmt
#endif

#include "test_includes.hpp"

#include <iostream>

BOOST_AUTO_TEST_CASE(basic_fmt_test)
{
	// print to stdout
	fmt::print("stdout: {}: {}:\n", __LINE__, __FILE__);

	// print to stdout
	fmt::print(stderr, "stderr: {}: {}:\n", __LINE__, __FILE__);

	std::cout << fmt::format("std::cout {}: {}:", __LINE__, __FILE__) << std::endl;

	std::cerr << fmt::format("std::cerr {}: {}:", __LINE__, __FILE__) << std::endl;
}
