#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_logging
#endif

#include "test_includes.hpp"

#include <iostream>

using namespace std::chrono;

class GlibTimeStampSource {
public:
	static uint64_t get_timestamp_microseconds() { return g_get_monotonic_time(); }
	// static int64_t get_timestamp_nanoseconds { return g_get_monotonic_time(); }
};

BOOST_AUTO_TEST_CASE(basic_logging_test)
{
	// use bool arg to indicate sync logging with async default?
	logging::initialize();

	//logging::set_sync();

	auto ostream_sink = std::make_shared<logging::OStreamSink>();

	logging::add_sink(ostream_sink);

	auto test_logger = logging::make_logger("test_logger");

	BOOST_REQUIRE (test_logger);

	BOOST_CHECK (test_logger->get_enabled());

	test_logger->write_record("This is a test message",
	                         "test thread",
	                         GlibTimeStampSource::get_timestamp_microseconds(),
	                         __LINE__,
	                         __FILE__,
	                         G_STRFUNC);

	// so async sink has a chance to handle message
	mojo::sleep(1);

	logging::remove_sink (ostream_sink);

	// need to quit before deinitialize or Records will not be deallocated
	//test_log.quit();
	logging::deinitialize();
}

BOOST_AUTO_TEST_CASE(basic_logging_enumerate_loggers_test)
{
	logging::initialize();

	auto logger1 = logging::make_logger("test_logger1");
	auto logger2 = logging::make_logger("test_logger2");

	BOOST_CHECK(logger1->get_domain() == "test_logger1");
	BOOST_CHECK(logger2->get_domain() == "test_logger2");

	std::set<std::shared_ptr<logging::Logger>> loggers = logging::get_loggers();

	BOOST_CHECK(loggers.size() == 2);

	logging::deinitialize();
}

logging::ASyncLog& get_macro_test_log()
{
	static logging::ASyncLog default_log;
	return default_log;
}

ThreadNameMap<logging::String>& get_macro_test_thread_map()
{
	static ThreadNameMap<logging::String> macro_test_map;
	return macro_test_map;
}

#define T_DECLARE_LOGGER(Name) extern const logging::Logger& Name_logger();

#define T_LOGGER(Log, Name)                                                    \
	const logging::Logger& Name_logger()                                          \
	{                                                                             \
		static const logging::Logger logger(Log, #Name);                             \
		return logger;                                                               \
	}

T_DECLARE_LOGGER(macro_test)

T_LOGGER(get_macro_test_log(), macro_test)

#define T_LOG(Name, Message)                                                   \
	Name_logger().write_record(Message,                                           \
	                           get_macro_test_thread_map().get_name(),            \
	                           GlibTimeStampSource::get_timestamp_microseconds(), \
	                           __LINE__,                                          \
	                           __FILE__,                                          \
	                           G_STRFUNC);

// Log a record of a function call
#define T_LOG_CALL(Name)                                                       \
	Name_logger().write_record("Timestamp",                                       \
	                           get_macro_test_thread_map().get_name(),            \
	                           GlibTimeStampSource::get_timestamp_microseconds(), \
	                           __LINE__,                                          \
	                           __FILE__,                                          \
	                           G_STRFUNC);

BOOST_AUTO_TEST_CASE(logging_macro_test)
{
	logging::initialize();
	get_macro_test_thread_map().insert_name("logging_macro_test_thread");

	T_LOG_CALL(macro_test);

	T_LOG(macro_test, "This is a test of logging macros");

	T_LOG_CALL(macro_test);
	get_macro_test_thread_map().erase_name("logging_macro_test_thread");

	// necessary to process records and free Record
	get_macro_test_log().quit();
	logging::deinitialize();
}

// Total number of bytes that have been allocated using operator new
std::size_t operator_new_bytes_allocated = 0;

// Current allocations made using operator new that are yet to be deallocated
std::size_t operator_new_allocation_count = 0;

// Total number of allocations made using operator new
std::size_t operator_new_allocation_total = 0;

std::atomic<bool> enable_global_debug_allocator_output;

void set_global_debug_allocator_output(bool on_off)
{
	enable_global_debug_allocator_output = on_off;
}

// need per thread allocators/stats
void* operator new(std::size_t sz) // throw(std::bad_alloc)
{
	operator_new_bytes_allocated += sz;
	if (enable_global_debug_allocator_output) {
		printf("\nAllocated %zu bytes using ::operator new()\n", sz);
	}
	++operator_new_allocation_count;
	++operator_new_allocation_total;
	return std::malloc(sz);
}

void operator delete(void* ptr) throw()
{
	--operator_new_allocation_count;
	std::free(ptr);
}

void print_operator_new_stats()
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

	AllocData alloc_data_before;

	{
		ScopedDebugAllocatorOutput debug_output;

		logging::Allocator<char> alloc;

		logging::String log_str =
		    format(alloc, "stdout: {}: {}:\n", __LINE__, __FILE__);

		// print to stdout
		std::cout << log_str << std::endl;
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
