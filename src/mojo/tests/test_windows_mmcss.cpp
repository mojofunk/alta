#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_windows_mmcss
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include "mojo/core/time/time.hpp"
#include "mojo/core/native/windows_mmcss.hpp"

#include <windows.h>

using namespace mojo;

BOOST_AUTO_TEST_CASE(test_windows_mmcss)
{
	BOOST_CHECK(mmcss::initialize());

	HANDLE task_handle;

	mmcss::set_thread_characteristics("Pro Audio", &task_handle);
	mmcss::set_thread_priority(task_handle, mmcss::AVRT_PRIORITY_NORMAL);

	// probably not necessary
	mojo::usleep(1000000);

	// TODO check that it has taken effect

	mmcss::revert_thread_characteristics(task_handle);

	BOOST_CHECK(mmcss::deinitialize());
}
