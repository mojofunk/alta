namespace logging {

Logger::Logger(Log& the_log, const char* const domain)
    : m_log(the_log)
    , m_domain(domain)
    , m_enabled(true)
{
}

void Logger::write_record(const char* const msg,
                          const String& thread_name,
                          uint64_t timestamp,
                          int line,
                          const char* file_name,
                          const char* function_name) const
{
	if (!m_enabled) {
		return;
	}

	// logging::create_record()?
	Record* record = new Record(
	    msg, m_domain, thread_name, timestamp, line, file_name, function_name);

	m_log.write_record(record);
}

} // namespace logging
