#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_logging
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <glib.h>

#include <map>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std::chrono;

class GlibTimeStampSource {
public:
	static uint64_t get_timestamp_microseconds() { return g_get_monotonic_time(); }
	// static int64_t get_timestamp_nanoseconds { return g_get_monotonic_time(); }
};

class ChronoTimeStampSource {
public:
	static uint64_t get_timestamp_microseconds()
	{
		auto duration = high_resolution_clock::now();
		return duration_cast<microseconds>(duration.time_since_epoch()).count();
	}
};

template <class T>
class ElapsedTimer {
public:
	ElapsedTimer()
	    : m_start_time(T::get_timestamp_microseconds())
	{
	}

	void restart() { m_start_time = T::get_timestamp_microseconds(); }

	std::uint64_t elapsed_usecs() const
	{
		return T::get_timestamp_microseconds() - m_start_time;
	}

private:
	std::uint64_t m_start_time;
};

class StdThreadMap {
public:
	void add_thread_name(const std::string& thread_name)
	{
		m_thread_name_map.insert(
		    std::make_pair(std::this_thread::get_id(), thread_name));
	}

	void remove_thread_name(const std::string& thread_name)
	{
		m_thread_name_map.erase(std::this_thread::get_id());
	}

	std::string get_thread_name()
	{
		ThreadNameMapType::const_iterator i =
		    m_thread_name_map.find(std::this_thread::get_id());

		if (i != m_thread_name_map.end()) {
			return i->second;
		}

		return "Unknown Thread";
	}

private:
	typedef std::map<std::thread::id, const std::string> ThreadNameMapType;
	ThreadNameMapType m_thread_name_map;
};

// may not need this class
struct SourceLocation {
	const int m_line;
	const char* m_file;
	const char* m_function;
};

/**
 * I think a log message should not take a std::string argument but rather a
 * LogString perhaps that is a basic_string with a custom allocator.
 *
 * Taking a begin and end iterators are another option but would force using
 * templates?
 *
 */
class LogRecord {
public:
	LogRecord(const std::string& message,
	          const char* const logger_name,
	          const std::string& thread_name,
	          uint64_t timestamp,
	          int line,
	          const char* const file_name,
	          const char* const function_name)
	    : m_message(message)
	    , m_logger_name(logger_name)
	    , m_thread_name(thread_name)
	    , m_timestamp(timestamp)
	    , m_line(line)
	    , m_file_name(file_name)
	    , m_function_name(function_name)
	{
	}

	const std::string m_message;

	const char* const m_logger_name;

	/**
	 * We don't want each message having a copy of the name
	 */
	const std::string m_thread_name;

	const uint64_t m_timestamp;

	const int m_line;
	const char* m_file_name;
	const char* m_function_name;
};

class LogSink {
public:
	virtual std::string name() = 0;

	virtual void handle_message(LogRecord& msg) = 0;
};

/**
 * Log should be an interface class with SyncLog and AsyncLog implementations?
 */
class Log {
public: // add loggers
public:
	void add_log_sink();

	void remove_log_sink();

public:
	// get loggers

public:
	void write_message(const std::string& message,
	                   const char* const logger_name,
	                   const std::string& thread_name,
	                   uint64_t timestamp,
	                   int line,
	                   const char* const file_name,
	                   const char* const function_name)
	{
		std::cout << "Logger: " << logger_name << ", Log Message: " << message
		          << ", Thread: " << thread_name << " Timestamp: " << timestamp
		          << ", Line: " << line << ", File Name: " << file_name
		          << ", Function: " << function_name << std::endl;

		// allocate a new log record from allocator

		// add log message to queue
	}
};

/**
 * The Logger class needs a reference to a Log instance to send the log message
 * to.
 *
 * The Logger class will only send the message if it is enabled.
 */
class Logger {
public:
	Logger(Log& log, const char* const logger_name)
	    : m_enabled(true)
	    , m_name(logger_name)
	    , m_log(log)
	{
	}

	const char* const get_name() const { return m_name; }

	bool get_enabled() const { return m_enabled; }
	void set_enabled(bool enable) { m_enabled = enable; }

	void send_message(const char* const msg,
	                  const std::string& thread_name,
	                  uint64_t timestamp,
	                  int line,
	                  const char* file_name,
	                  const char* function_name) const
	{
		if (!m_enabled) {
			return;
		}

		m_log.write_message(
		    msg, m_name, thread_name, timestamp, line, file_name, function_name);
	}

private:
	const char* const m_name;

	bool m_enabled; // should probably be atomic

	Log& m_log;
};

// static allocator set/get or per Log allocator?

// macros

StdThreadMap s_test_thread_map;

BOOST_AUTO_TEST_CASE(basic_logging_test)
{
	Log test_log;

	s_test_thread_map.add_thread_name("thread");

	Logger test_logger(test_log, "test_logger");

	test_logger.send_message("This is a test message",
	                         s_test_thread_map.get_thread_name(),
	                         GlibTimeStampSource::get_timestamp_microseconds(),
	                         __LINE__,
	                         __FILE__,
	                         G_STRFUNC);
}

Log& get_macro_test_log()
{
	static Log default_log;
	return default_log;
}

StdThreadMap& get_macro_test_thread_map()
{
	static StdThreadMap macro_test_map;
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

#define T_LOG(Name, LogString)                                                 \
	Name_logger().send_message(LogString,                                         \
	                           get_macro_test_thread_map().get_thread_name(),     \
	                           GlibTimeStampSource::get_timestamp_microseconds(), \
	                           __LINE__,                                          \
	                           __FILE__,                                          \
	                           G_STRFUNC);

// Log a record of a function call
#define T_LOG_CALL(Name)                                                       \
	Name_logger().send_message("Timestamp",                                       \
	                           get_macro_test_thread_map().get_thread_name(),     \
	                           GlibTimeStampSource::get_timestamp_microseconds(), \
	                           __LINE__,                                          \
	                           __FILE__,                                          \
	                           G_STRFUNC);

BOOST_AUTO_TEST_CASE(logging_macro_test)
{
	get_macro_test_thread_map().add_thread_name("logging_macro_test_thread");

	T_LOG_CALL(macro_test);

	T_LOG(macro_test, "This is a test of logging macros");

	T_LOG_CALL(macro_test);
}
