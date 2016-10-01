namespace logging {

Logger::Logger(Log& the_log, const char* const domain)
    : m_log(the_log)
    , m_domain(domain)
    , m_enabled(true)
{
}

void Logger::write_record(const String& msg,
                          const uint32_t cpu_id,
                          const std::thread::id thread_id,
                          uint64_t timestamp,
                          int line,
                          const char* file_name,
                          const char* function_name) const
{
	if (!m_enabled) {
		return;
	}

	// logging::create_record()?
	Record* record = new Record(msg,
	                            m_domain,
	                            cpu_id,
	                            thread_id,
	                            timestamp,
	                            line,
	                            file_name,
	                            function_name);

	m_log.write_record(record);
}

} // namespace logging
