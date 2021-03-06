#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_logging
#endif

#include "test_includes.hpp"

#include <iostream>

using namespace std::chrono;

class GlibTimeStampSource
{
public:
	static uint64_t get_timestamp_microseconds() { return g_get_monotonic_time(); }
	// static int64_t get_timestamp_nanoseconds { return g_get_monotonic_time(); }
};

BOOST_AUTO_TEST_CASE(test_logging_init)
{
	logging::initialize();
	logging::deinitialize();

	logging::initialize();
	logging::deinitialize();
}

BOOST_AUTO_TEST_CASE(basic_logging_test)
{
	// use bool arg to indicate sync logging with async default?
	logging::initialize();

	// logging::set_sync();

	auto ostream_sink = std::make_shared<logging::OStreamSink>();

	logging::add_sink(ostream_sink.get());

	auto test_logger = logging::get_logger("test_logger");

	BOOST_REQUIRE(test_logger);

	BOOST_CHECK(test_logger->get_enabled());

	test_logger->write_record("This is a test message",
	                          get_cpu_id(),
	                          std::this_thread::get_id(),
	                          logging::TimeStamp::get_microseconds(),
	                          __LINE__,
	                          __FILE__,
	                          M_STRFUNC);

	// so async sink has a chance to handle message
	mojo::sleep(1);

	logging::remove_sink(ostream_sink.get());

	// need to quit before deinitialize or Records will not be deallocated
	// test_log.quit();
	logging::deinitialize();
}

BOOST_AUTO_TEST_CASE(basic_logging_enumerate_loggers_test)
{
	logging::initialize();

	auto logger1 = logging::get_logger("test_logger1");
	auto logger2 = logging::get_logger("test_logger2");

	BOOST_CHECK(logger1->get_domain() == "test_logger1");
	BOOST_CHECK(logger2->get_domain() == "test_logger2");

	std::set<logging::Logger*> loggers = logging::get_loggers();

	BOOST_CHECK(loggers.size() == 2);

	logging::deinitialize();
}

BOOST_AUTO_TEST_CASE(logging_macro_test)
{
	const char* const thread_name = "logging_macro_test_thread";

	logging::initialize();

	auto ostream_sink = std::make_shared<logging::OStreamSink>();

	logging::add_sink(ostream_sink.get());

	logging::register_thread_name(thread_name);

	BOOST_CHECK(logging::thread_name(std::this_thread::get_id()) == thread_name);

	M_DEFINE_LOGGER(MacroLogger);
	M_GET_LOGGER(MacroLogger);

	M_LOG_CALL(MacroLogger);

	M_LOG(MacroLogger, "This is a test of logging macros");

	M_LOG_CALL(MacroLogger);

	mojo::sleep(1);

	logging::deregister_thread_name();
	logging::deinitialize();
}

static std::atomic<bool> test_logging_alloc_done(false);

M_DEFINE_LOGGER(ThreadTestLogger);

void
test_logging_alloc_thread()
{
	cout << "Started Perf thread" << endl;
	while (!test_logging_alloc_done) {
		M_LOG_CALL(ThreadTestLogger);
		// The amount of log messages per unit of time will determine how large the
		// pool will need to be to avoid allocation from global new/heap. If the
		// sleep call is removed then the logging thread will more than likely not
		// be able to process records fast enough to free up memory to avoid heap
		// allocation.
		mojo::usleep(g_random_int_range(200, 600));
	}
}

void
test_logging_alloc_iteration()
{
	test_logging_alloc_done = false;
	const int num_logging_threads = 4;

	std::vector<std::thread> logging_threads;

	for (int i = 0; i != num_logging_threads; ++i) {
		logging_threads.push_back(std::thread(test_logging_alloc_thread));
	}

	mojo::sleep(10);

	test_logging_alloc_done = true;

	for (auto& t : logging_threads) {
		BOOST_CHECK_NO_THROW(t.join());
	}
}

BOOST_AUTO_TEST_CASE(logging_alloc_test)
{
	logging::initialize();

	auto ostream_sink = std::make_shared<logging::OStreamSink>();

	logging::add_sink(ostream_sink.get());

	M_GET_LOGGER(ThreadTestLogger);

	test_logging_alloc_iteration();

	logging::deinitialize();
}

// Total number of bytes that have been allocated using operator new
std::size_t operator_new_bytes_allocated = 0;

// Current allocations made using operator new that are yet to be deallocated
std::size_t operator_new_allocation_count = 0;

// Total number of allocations made using operator new
std::size_t operator_new_allocation_total = 0;

std::atomic<bool> enable_global_debug_allocator_output;

void
set_global_debug_allocator_output(bool on_off)
{
	enable_global_debug_allocator_output = on_off;
}

// need per thread allocators/stats
void*
operator new(std::size_t sz) // throw(std::bad_alloc)
{
	operator_new_bytes_allocated += sz;
	if (enable_global_debug_allocator_output) {
		printf("\nAllocated %zu bytes using ::operator new()\n", sz);
	}
	++operator_new_allocation_count;
	++operator_new_allocation_total;
	return std::malloc(sz);
}

void
operator delete(void* ptr) throw()
{
	--operator_new_allocation_count;
	std::free(ptr);
}

void
print_operator_new_stats()
{
	std::cout << "Total bytes allocated using ::operator new = "
	          << operator_new_bytes_allocated << '\n';

	std::cout << "Current allocation count ::operator new = "
	          << operator_new_allocation_count << '\n';

	std::cout << "Total allocation count ::operator new = "
	          << operator_new_allocation_total << '\n';
}

struct ScopedDebugAllocatorOutput {
	ScopedDebugAllocatorOutput() { set_global_debug_allocator_output(true); }

	~ScopedDebugAllocatorOutput() { set_global_debug_allocator_output(false); }
};

struct AllocData {
	AllocData(std::size_t bytes = operator_new_bytes_allocated,
	          std::size_t count = operator_new_allocation_count,
	          std::size_t total = operator_new_allocation_total)
	    : m_bytes(bytes)
	    , m_count(count)
	    , m_total(total)
	{
	}

	AllocData(const AllocData& other) = default;

	const std::size_t m_bytes;
	const std::size_t m_count;
	const std::size_t m_total;

	bool operator==(const AllocData& other)
	{
		return (m_bytes == other.m_bytes && m_count == other.m_count &&
		        m_total == other.m_total);
	}

	bool operator!=(const AllocData& other) { return !operator==(other); }
};

BOOST_AUTO_TEST_CASE(alloc_data_test)
{
	ScopedDebugAllocatorOutput debug_output;

	AllocData alloc_data_before;

	const std::size_t vec_size = 4096;
	const std::size_t bytes_allocated = vec_size * sizeof(int);

	std::vector<int> int_vec;
	int_vec.reserve(vec_size);

	AllocData alloc_data_after;

	BOOST_CHECK(alloc_data_before != alloc_data_after);

	BOOST_CHECK(alloc_data_before.m_bytes + bytes_allocated ==
	            alloc_data_after.m_bytes);
}

BOOST_AUTO_TEST_CASE(log_string_test)
{
	ScopedDebugAllocatorOutput debug_output;

	std::cout << "logging::initialize()" << std::endl;
	logging::initialize();

	AllocData alloc_data_before;
	{
		std::cout << "create log_string()" << std::endl;
		logging::String log_string("String test string");

		std::cout << log_string << std::endl;
	}
	AllocData alloc_data_after;

	std::cout << "destroy log_string" << std::endl;

	// check there has been no allocations using operator new
	BOOST_CHECK(alloc_data_before == alloc_data_after);

	logging::deinitialize();
	print_operator_new_stats();
}

BOOST_AUTO_TEST_CASE(log_format_test)
{
	logging::initialize();

	M_DEFINE_LOGGER(FormatLogger);
	M_GET_LOGGER(FormatLogger);

	AllocData alloc_data_before;

	{
		ScopedDebugAllocatorOutput debug_output;

		logging::Allocator<char> alloc;

		logging::String log_str =
		    format(alloc, "stdout: {}: {}:\n", __LINE__, __FILE__);

		std::cout << log_str << std::endl;

		logging::String format_str =
		    M_FORMAT("stdout: {}: {}: {}\n", __LINE__, __FILE__, M_STRFUNC);

		std::cout << format_str << std::endl;

		M_LOG_CALL(FormatLogger);

		M_LOG(FormatLogger, format_str);

		M_LOG_CALL(FormatLogger);
	}

	AllocData alloc_data_after;

	// check there has been no allocations using operator new
	BOOST_CHECK(alloc_data_before == alloc_data_after);

	logging::deinitialize();
}

BOOST_AUTO_TEST_CASE(logging_no_cache_test)
{
	/**
	 * Test that logging still works without using a cache for logging strings
	 * etc. call logging::initialize with empty CacheOptions/LogNoCacheOption
	 */
}
