namespace logging {

static std::atomic<uint32_t> s_init_logging_count(0);

static ASyncLog* s_log = nullptr;

static Sink* s_default_sink = nullptr;

static ThreadNameRegistry<String>* s_thread_name_registry = nullptr;

void initialize()
{
	if (++s_init_logging_count != 1) return;

	initialize_allocator();
	s_log = new ASyncLog;
	s_default_sink = new OStreamSink;
	s_log->add_sink(s_default_sink);
	s_thread_name_registry = new ThreadNameRegistry<String>;
}

void deinitialize()
{
	if (--s_init_logging_count != 0) return;

	delete s_thread_name_registry;
	s_thread_name_registry = nullptr;
	s_log->remove_sink(s_default_sink);
	delete s_default_sink;
	s_default_sink = nullptr;
	delete s_log;
	s_log = nullptr;
	deinitialize_allocator();
}

void add_sink(Sink* sink_ptr)
{
	s_log->remove_sink(s_default_sink);
	s_log->add_sink(sink_ptr);
}

void remove_sink(Sink* sink_ptr)
{
	s_log->remove_sink(sink_ptr);
	if (s_log->get_sinks().empty()) {
		s_log->add_sink(s_default_sink);
	}
}

std::set<Sink*> get_sinks()
{
	return s_log->get_sinks();
}

void write_record(Record* record)
{
	s_log->write_record(record);
}

Logger* get_logger(const char* const domain)
{
	return s_log->get_logger(domain);
}

std::set<Logger*> get_loggers()
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
