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

// may not need this class
struct SourceLocation {
	const int m_line;
	const char* m_file;
	const char* m_function;
};

struct LogRecord {
	LogRecord(const LogString& p_message,
	          const char* const p_logger_name,
	          const LogString& p_thread_name,
	          uint64_t p_timestamp,
	          int p_line,
	          const char* const p_file_name,
	          const char* const p_function_name)
	    : message(p_message)
	    , logger_name(p_logger_name)
	    , thread_name(p_thread_name)
	    , timestamp(p_timestamp)
	    , line(p_line)
	    , file_name(p_file_name)
	    , function_name(p_function_name)
	{
	}

	const LogString message;

	const LogString logger_name;

	const LogString thread_name;

	const uint64_t timestamp;

	const int line;

	// copy these as if a dll that contains a Logger and is
	// unloaded the addresses will be invalid...perf impact?
	const LogString file_name;
	const LogString function_name;

public: // class new/delete

	void* operator new(size_t size)
	{
		std::cout << "new LogRecord" << std::endl;
		return log_malloc(size);
	}

	void operator delete(void* ptr)
	{
		std::cout << "delete LogRecord" << std::endl;
		log_free(ptr);
	}
};

class LogSink {
public:
	virtual std::string name() = 0;

	/*
	 * The LogRecord is only valid for the handle_record call.
	 */
	virtual void handle_record(LogRecord& record) = 0;
};

class OStreamLogSink : public LogSink {
public:
	std::string name() override { return "OStreamLogSink"; }

	void handle_record(LogRecord& record) override
	{
		std::cout << "Logger: " << record.logger_name
		          << ", Log Message: " << record.message
		          << ", Thread: " << record.thread_name
		          << " Timestamp: " << record.timestamp << ", Line: " << record.line
		          << ", File Name: " << record.file_name
		          << ", Function: " << record.function_name << std::endl;
	}

};

class Logger;

/**
 * Log should be an interface class with SyncLog and AsyncLog implementations?
 *
 * Or should it be static/singleton and be renamed Logging
 */
class Log : public mojo::Worker {
public:
	Log()
	    : m_record_queue(32768 * 4) // max capacity, max threads
	    , m_record_processing_thread(&Log::run, this)
	{
		// wait for run loop to start
		iteration(true);
	}

	~Log()
	{
		// don't allow messages to be queued during destruction
		quit();
		m_record_processing_thread.join();

		// process/drop any log messages still left in queue
		process_records();

	}

public: // add sinks
	void add_log_sink(LogSink* sink)
	{
		std::unique_lock<std::mutex> lock(m_sinks_mutex);
		m_sinks.insert(sink);
	}

	void remove_log_sink(LogSink* sink)
	{
		std::unique_lock<std::mutex> lock(m_sinks_mutex);
		m_sinks.erase(sink);
	}

private:

	// TODO May need a way to signal that a Logger has been removed for listening
	// classes

	friend class Logger;

	// could probably pass delete handler to shared_ptr to avoid these with
	// create_logger API

	// @return true if logger with added, false if logger found with same name?
	bool add_logger (Logger* logger)
	{
		std::unique_lock<std::mutex> lock(m_loggers_mutex);
		m_loggers.insert(logger);
	}

	// @return true if logger was removed or false if not found?
	bool remove_logger (Logger* logger)
	{
		std::unique_lock<std::mutex> lock(m_loggers_mutex);
		m_loggers.erase(logger);
	}

public: // Log interface
	void write_record(LogRecord* record)
	{
		if (m_quit) return;

		if (!m_record_queue.try_enqueue(record)) {
//#ifdef LOG_DEBUG
			std::cout << "Unable to enqueue LogRecord using non-blocking API"
			          << std::endl;
//#endif
			m_record_queue.enqueue(record);
			iteration(false);
		}
	}

private: // run loop

	void do_work () override
	{
		process_records ();
	}

	void process_records ()
	{
		LogRecord* record = nullptr;

		while (m_record_queue.try_dequeue(record)) {
			std::unique_lock<std::mutex> lock(m_sinks_mutex);
			for (auto sink : m_sinks) {
				sink->handle_record (*record);
			}
			delete record;
		}
	}

private: // data

	// queue for LogRecords
	using RecordQueueType = moodycamel::ConcurrentQueue<LogRecord*>;
	RecordQueueType m_record_queue;

	// set of LogSink
	std::set<LogSink*> m_sinks;
	std::mutex m_sinks_mutex;

	// set of Loggers
	std::set<Logger*> m_loggers;
	std::mutex m_loggers_mutex;

	std::thread m_record_processing_thread;
};

/**
 * The Logger class needs a reference to a Log instance to send the log message
 * to or does it just send it to a singleton class/static method in mojo core
 *
 * The Logger class will only send the message if it is enabled.
 */
class Logger {
public:
	Logger(Log& logg, const char* const logger_name)
	    : m_enabled(true)
	    , m_name(logger_name)
	    , m_log(logg)
	{
		m_log.add_logger(this);
	}

	~Logger ()
	{
		m_log.remove_logger(this);
	}

	const char* const get_name() const { return m_name; }

	bool get_enabled() const { return m_enabled; }
	void set_enabled(bool enable) { m_enabled = enable; }

	/**
	 * The logging API could expose a ThreadNameMap<LogString>
	 * that the Logging classes look up to get the thread name which seems to
	 * make more sense that allowing callers to specify which thread to log the
	 * message in as they may get it wrong for some reason.
	 */
	void send_message(const char* const msg,
	                  const LogString& thread_name,
	                  uint64_t timestamp,
	                  int line,
	                  const char* file_name,
	                  const char* function_name) const
	{
		if (!m_enabled) {
			return;
		}

		LogRecord* record = new LogRecord(msg,
		                                  m_name,
		                                  thread_name,
		                                  timestamp,
		                                  line,
		                                  file_name,
		                                  function_name);

		m_log.write_record(record);
	}

private:
	const char* const m_name;

	bool m_enabled; // should probably be atomic

	Log& m_log;
};

// static allocator set/get or per Log allocator?

// macros

BOOST_AUTO_TEST_CASE(basic_logging_test)
{
	log_initialize();

	Log test_log;

	Logger test_logger(test_log, "test_logger");

	OStreamLogSink stream_sink;
	test_log.add_log_sink(&stream_sink);

	// add alloc tracking

	test_logger.send_message("This is a test message",
	                         "test thread",
	                         GlibTimeStampSource::get_timestamp_microseconds(),
	                         __LINE__,
	                         __FILE__,
	                         G_STRFUNC);

	// need to quit before deinitialize or Records will not be deallocated
	test_log.quit();
	log_deinitialize();
}

Log& get_macro_test_log()
{
	static Log default_log;
	return default_log;
}

ThreadNameMap<LogString>& get_macro_test_thread_map()
{
	static ThreadNameMap<LogString> macro_test_map;
	return macro_test_map;
}

#define T_DECLARE_LOGGER(Name) extern const Logger& Name_logger();

#define T_LOGGER(Log, Name)                                                    \
	const Logger& Name_logger()                                                   \
	{                                                                             \
		static const Logger logger(Log, #Name);                                      \
		return logger;                                                               \
	}

T_DECLARE_LOGGER(macro_test)

T_LOGGER(get_macro_test_log(), macro_test)

#define T_LOG(Name, Message)                                                   \
	Name_logger().send_message(Message,                                           \
	                           get_macro_test_thread_map().get_name(),            \
	                           GlibTimeStampSource::get_timestamp_microseconds(), \
	                           __LINE__,                                          \
	                           __FILE__,                                          \
	                           G_STRFUNC);

// Log a record of a function call
#define T_LOG_CALL(Name)                                                       \
	Name_logger().send_message("Timestamp",                                       \
	                           get_macro_test_thread_map().get_name(),            \
	                           GlibTimeStampSource::get_timestamp_microseconds(), \
	                           __LINE__,                                          \
	                           __FILE__,                                          \
	                           G_STRFUNC);

BOOST_AUTO_TEST_CASE(logging_macro_test)
{
	log_initialize();
	get_macro_test_thread_map().insert_name("logging_macro_test_thread");

	T_LOG_CALL(macro_test);

	T_LOG(macro_test, "This is a test of logging macros");

	T_LOG_CALL(macro_test);
	get_macro_test_thread_map().erase_name("logging_macro_test_thread");

	// necessary to process records and free LogRecord
	get_macro_test_log().quit();
	log_deinitialize();
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

	std::cout << "log_initialize()" << std::endl;
	log_initialize();

	AllocData alloc_data_before;
	{
		std::cout << "create log_string()" << std::endl;
		LogString log_string("LogString test string");

		std::cout << log_string << std::endl;
	}
	AllocData alloc_data_after;

	std::cout << "destroy log_string" << std::endl;

	// check there has been no allocations using operator new
	BOOST_CHECK(alloc_data_before == alloc_data_after);

	log_deinitialize();
	print_operator_new_stats();
}

BOOST_AUTO_TEST_CASE(log_format_test)
{
	log_initialize();

	AllocData alloc_data_before;

	{
		ScopedDebugAllocatorOutput debug_output;

		LogAllocator<char> alloc;

		LogString log_str =
		    log_format(alloc, "stdout: {}: {}:\n", __LINE__, __FILE__);

		// print to stdout
		std::cout << log_str << std::endl;
	}

	AllocData alloc_data_after;

	// check there has been no allocations using operator new
	BOOST_CHECK(alloc_data_before == alloc_data_after);

	log_deinitialize();
}

BOOST_AUTO_TEST_CASE(logging_no_cache_test)
{
	/**
	 * Test that logging still works without using a cache for logging strings
	 * etc. call log_initialize with empty CacheOptions/LogNoCacheOption
	 */
}
