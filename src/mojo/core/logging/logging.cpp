namespace logging {

static std::atomic<uint32_t> s_init_logging_count(0);

static mojo::FixedSizePool* s_log_mem_pool = nullptr;

static ASyncLog* s_log = nullptr;

void initialize()
{
	if (++s_init_logging_count != 1) return;

	s_log_mem_pool = new FixedSizePool(128, 1024);
	s_log = new ASyncLog;
}

void deinitialize()
{
	if (--s_init_logging_count != 0) return;

	delete s_log;
	s_log = 0;
	delete s_log_mem_pool;
	s_log_mem_pool = 0;
}

void* allocate(std::size_t size)
{
	void* ptr = 0;

	std::cout << "allocate(" << size << ") = ";

	assert(s_log_mem_pool);

	if (size > s_log_mem_pool->max_size()) {
		std::cout << "log allocating using operator new" << std::endl;
		ptr = ::operator new(size);
	} else {
		std::cout << "log allocating using log pool" << std::endl;
		ptr = s_log_mem_pool->allocate(size);
		std::cout << "log pool available : " << s_log_mem_pool->available()
		          << std::endl;
	}

	return ptr;
}

void deallocate(void* ptr)
{
	if (s_log_mem_pool->is_from(ptr)) {
		std::cout << "log deallocating using mem pool" << std::endl;
		s_log_mem_pool->deallocate(ptr);
	} else {
		std::cout << "log deallocating using std::free" << std::endl;
		::operator delete(ptr);
	}
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

} // namespace logging
