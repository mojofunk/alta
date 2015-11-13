#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_windows_mmcss
#endif

#include "test_includes.hpp"

#include <windows.h>

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
