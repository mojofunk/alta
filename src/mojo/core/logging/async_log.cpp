namespace logging {

ASyncLog::ASyncLog()
    : m_record_queue(32768 * 4) // max capacity, max threads
    , m_record_processing_thread(&ASyncLog::run, this)
{
	// wait for run loop to start
	iteration(true);
}

ASyncLog::~ASyncLog()
{
	// don't allow messages to be queued during destruction
	quit();
	m_record_processing_thread.join();

	// process/drop any log messages still left in queue
	process_records();
}

void ASyncLog::add_sink(std::shared_ptr<Sink> sink)
{
	std::unique_lock<std::mutex> lock(m_sinks_mutex);
	m_sinks.insert(sink);
}

void ASyncLog::remove_sink(std::shared_ptr<Sink> sink)
{
	std::unique_lock<std::mutex> lock(m_sinks_mutex);
	m_sinks.erase(sink);
}

void ASyncLog::write_record(Record* record)
{
	if (m_quit) return;

	if (!m_record_queue.try_enqueue(record)) {
		LOGGING_DEBUG("Unable to enqueue Record using non-blocking API");
		m_record_queue.enqueue(record);
	}
	iteration(false);
}

std::shared_ptr<Logger> ASyncLog::make_logger(const char* const domain)
{
	auto logger = std::make_shared<Logger>(*this, domain);
	std::unique_lock<std::mutex> lock(m_loggers_mutex);
	m_loggers.insert(logger);
	return logger;
}

std::set<std::shared_ptr<Logger>> ASyncLog::get_loggers() const
{
	std::unique_lock<std::mutex> lock(m_loggers_mutex);
	auto tmp = m_loggers;
	return tmp;
}

void ASyncLog::do_work()
{
	process_records();
}

void ASyncLog::process_records()
{
	Record* record = nullptr;

	while (m_record_queue.try_dequeue(record)) {
		std::unique_lock<std::mutex> lock(m_sinks_mutex);
		for (auto sink : m_sinks) {
			sink->handle_record(*record);
		}
		LOGGING_DEBUG("Deleting Record");
		delete record;
	}
}

} // namespace logging
