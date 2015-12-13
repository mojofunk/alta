#ifndef MOJO_LOGGING_LOG_H
#define MOJO_LOGGING_LOG_H

namespace logging {

class Log {
public: // Log interface
	virtual void add_sink(std::shared_ptr<Sink> sink) = 0;

	virtual void remove_sink(std::shared_ptr<Sink> sink) = 0;

	// @return true if logger with added, false if logger found with same name?
	virtual bool add_logger (std::shared_ptr<Logger> logger) = 0;

	// @return true if logger was removed or false if not found?
	virtual bool remove_logger (std::shared_ptr<Logger> logger) = 0;

	virtual void write_record(Record* record) = 0;

	virtual std::shared_ptr<Logger> make_logger(const char* const domain) = 0;

	virtual std::set<std::shared_ptr<Logger>> get_loggers() const = 0;
};

} // namespace logging

void log(const char* log_domain, const std::string& msg);

#endif // MOJO_LOGGING_LOG_H
