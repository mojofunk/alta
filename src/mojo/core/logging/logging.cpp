namespace logging {

static std::atomic<uint32_t> s_init_logging_count(0);

static ASyncLog* s_log = nullptr;

static ThreadNameRegistry<String>* s_thread_name_registry = nullptr;

void initialize()
{
	if (++s_init_logging_count != 1) return;

	initialize_allocator();
	s_log = new ASyncLog;
	s_thread_name_registry = new ThreadNameRegistry<String>;
}

void deinitialize()
{
	if (--s_init_logging_count != 0) return;

	delete s_thread_name_registry;
	s_thread_name_registry = nullptr;
	delete s_log;
	s_log = nullptr;
	deinitialize_allocator();
}

void add_sink(std::shared_ptr<Sink> sink_ptr)
{
	s_log->add_sink(sink_ptr);
}

void remove_sink(std::shared_ptr<Sink> sink_ptr)
{
	s_log->remove_sink(sink_ptr);
}

void add_logger (std::shared_ptr<Logger> logger)
{
	s_log->add_logger(logger);
}

void remove_logger (std::shared_ptr<Logger> logger)
{
	s_log->remove_logger(logger);
}

void write_record(Record* record)
{
	s_log->write_record(record);
}

std::shared_ptr<Logger> make_logger(const char* const logging_domain)
{
	return s_log->make_logger(logging_domain);
}

std::set<std::shared_ptr<Logger>> get_loggers()
{
	return s_log->get_loggers();
}

void register_thread_name(const char* const thread_name)
{
	s_thread_name_registry->register_thread(thread_name);
}

void deregister_thread_name()
{
	s_thread_name_registry->unregister_thread();
}

String thread_name()
{
	return s_thread_name_registry->get_thread_name();
}

} // namespace logging
