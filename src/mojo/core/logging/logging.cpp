static mojo::FixedSizePool* s_log_mem_pool;

void log_initialize()
{
	s_log_mem_pool = new FixedSizePool(128, 1024);
}

void log_deinitialize()
{
	delete s_log_mem_pool;
	s_log_mem_pool = 0;
}

void* log_malloc(std::size_t size)
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

void log_free(void* ptr)
{
	if (s_log_mem_pool->is_from(ptr)) {
		std::cout << "log deallocating using mem pool" << std::endl;
		s_log_mem_pool->deallocate(ptr);
	} else {
		std::cout << "log deallocating using std::free" << std::endl;
		::operator delete(ptr);
	}
}
