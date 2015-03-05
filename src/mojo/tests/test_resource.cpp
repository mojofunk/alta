#define BOOST_TEST_MODULE mojo_resource

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include "mojo/core/system/resource.hpp"
#include "mojo/core/string/compose.hpp"

#include "test_common.hpp"

using namespace boost::unit_test;
using namespace mojo;

BOOST_AUTO_TEST_CASE( open_files_resource_limit_test )
{
	ResourceLimit limit;
	BOOST_CHECK (get_resource_limit (OpenFiles, limit));
	BOOST_TEST_MESSAGE(compose ("Current open files %",
		limit.current_limit));
	BOOST_TEST_MESSAGE(compose ("Max open files %",
		limit.max_limit));

}

BOOST_AUTO_TEST_CASE( mem_lock_resource_limit_test )
{
	ResourceLimit limit;
	BOOST_CHECK (get_resource_limit (MemLock, limit));
	BOOST_TEST_MESSAGE(compose ("Current locked memory limit %",
		limit.current_limit));
	BOOST_TEST_MESSAGE(compose ("Max locked memory limit %",
		limit.max_limit));
}

BOOST_AUTO_TEST_CASE( physical_memory_size_test )
{
	int64_t memory_size = physical_memory_size ();
	BOOST_CHECK (memory_size != 0);
	BOOST_TEST_MESSAGE(compose ("Physical memory size %", memory_size));
}
