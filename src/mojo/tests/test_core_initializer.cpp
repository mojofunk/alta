#define BOOST_TEST_MODULE mojo_core_initializer

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <thread>

#include "mojo/core/init/initialize.hpp"
#include "mojo/core/time/time.hpp"

using namespace mojo;

std::atomic_bool s_exit(false);

void
init_thread ()
{
	while (!s_exit) {
		std::list<std::unique_ptr<CoreInitializer>> init_list;

		init_list.push_back (std::unique_ptr<CoreInitializer>(new CoreInitializer));
	}
}

BOOST_AUTO_TEST_CASE( test_core_initializer )
{
	BOOST_REQUIRE(!CoreInitializer::initialized());

	std::thread thread1(init_thread);
	std::thread thread2(init_thread);

	mojo::usleep(10*1000000);

	s_exit = true;

	thread1.join();
	thread2.join();

	BOOST_CHECK(!CoreInitializer::initialized());
}
