#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_stack_trace
#endif

#include "test_includes.hpp"

#include <iostream>

BOOST_AUTO_TEST_CASE(test_stack_trace_print)
{
	StackTrace trace;
	trace.print();
	trace.print(3);
	std::size_t count = 0;
	trace.get_addresses(count);
	BOOST_CHECK(count != 0);
}

BOOST_AUTO_TEST_CASE(test_stack_trace_to_stream)
{
	StackTrace trace;
	trace.to_stream(std::cout);
	trace.to_stream(std::cout, 50);
	std::string str = trace.to_string();
	std::size_t found = str.find("test_stack_trace_to_stream");
	BOOST_CHECK(found != std::string::npos);
}

BOOST_AUTO_TEST_CASE(test_stack_trace_to_string)
{
	StackTrace trace;
	std::string st_string(trace.to_string());
	std::cout << st_string << std::endl;
	std::size_t found = st_string.find("test_stack_trace_to_string");
	BOOST_CHECK(found != std::string::npos);
}

BOOST_AUTO_TEST_CASE(test_stack_trace_operator_equals)
{
	StackTrace traces[2];
	BOOST_CHECK(traces[0] == traces[1]);
}
