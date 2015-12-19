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
	destroy_loggers();
}

void
ASyncLog::destroy_loggers()
{
	// no need to lock in dtor

	for (auto logger : m_loggers) {
		delete logger;
	}
}

void ASyncLog::add_sink(Sink* sink)
{
	std::unique_lock<std::mutex> lock(m_sinks_mutex);
	m_sinks.insert(sink);
}

void ASyncLog::remove_sink(Sink* sink)
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

Logger* ASyncLog::get_logger(const char* const domain)
{
	// search for existing logger
	std::unique_lock<std::mutex> lock(m_loggers_mutex);

	// do we want to compare addresses or string equality or just make a new
	// logger anyway even if strings are equal.

	Logger* logger = new Logger(*this, domain);
	m_loggers.insert(logger);
	return logger;
}

std::set<Logger*> ASyncLog::get_loggers() const
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
