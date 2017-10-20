#ifndef MOJO_LOGGING_LOG_H
#define MOJO_LOGGING_LOG_H

namespace logging
{

class Log
{
public: // Log interface
	virtual void add_sink(Sink* sink) = 0;

	virtual void remove_sink(Sink* sink) = 0;

	virtual std::set<Sink*> get_sinks() const = 0;

	virtual void write_record(Record* record) = 0;

	/**
	 * The lifetime of the Logger instance is tied to the Log
	 * It is up to callers to assure that no references to the Loggers are
	 * referenced after the Log instance has been destroyed.
	 */
	virtual Logger* get_logger(const char* const domain) = 0;

	virtual std::set<Logger*> get_loggers() const = 0;
};

} // namespace logging

void
log(const char* log_domain, const std::string& msg);

#endif // MOJO_LOGGING_LOG_H
