namespace logging {

static std::atomic<uint32_t> s_allocator_init_count(0);

static FixedSizePool* s_allocator_mem_pool = nullptr;

void initialize_allocator()
{
	if (++s_allocator_init_count != 1) return;

	assert(s_allocator_mem_pool == nullptr);
	s_allocator_mem_pool = new FixedSizePool(128, 1024);
}

void deinitialize_allocator()
{
	if (--s_allocator_init_count != 0) return;

	delete s_allocator_mem_pool;
	s_allocator_mem_pool = nullptr;
}

void* logging_allocate(std::size_t size)
{
	void* ptr = 0;

	assert(s_allocator_mem_pool);

	if (size > s_allocator_mem_pool->max_size()) {
		LOGGING_DEBUG("logging allocator allocating (%d) bytes using global new", size);
		ptr = ::operator new(size);
	} else {
		LOGGING_DEBUG("logging allocator allocating (%d) bytes using pool", size);
		ptr = s_allocator_mem_pool->allocate(size);
		LOGGING_DEBUG("log pool available %d", s_allocator_mem_pool->available());
	}

	return ptr;
}

void logging_deallocate(void* ptr)
{
	if (s_allocator_mem_pool->is_from(ptr)) {
		LOGGING_DEBUG("log deallocating using mem pool");
		s_allocator_mem_pool->deallocate(ptr);
	} else {
		LOGGING_DEBUG("log deallocating using global delete");
		::operator delete(ptr);
	}
}

} // namespace logging
