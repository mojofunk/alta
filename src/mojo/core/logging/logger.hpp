#ifndef MOJO_LOGGING_LOGGER_H
#define MOJO_LOGGING_LOGGER_H

namespace logging
{

/**
 * The Logger class needs a reference to a Log instance to send the log message
 * to or does it just send it to a singleton class/static method in mojo core
 *
 * The Logger class will only send the message if it is enabled.
 */
class Logger
{
public:
	Logger(Log& the_log, const char* const domain);

	~Logger() = default;

	const char* const get_domain() const { return m_domain; }

	bool get_enabled() const { return m_enabled; }
	void set_enabled(bool enable) { m_enabled = enable; }

	void write_record(const String& msg,
	                  const uint32_t cpu_id,
	                  const std::thread::id thread_id,
	                  uint64_t timestamp,
	                  int line,
	                  const char* file_name,
	                  const char* function_name) const;

private:
	Log& m_log;

	// I think we want to copy this
	const char* const m_domain;

	bool m_enabled; // should probably be atomic
};

} // namespace logging

#endif // MOJO_LOGGING_LOGGER_H
