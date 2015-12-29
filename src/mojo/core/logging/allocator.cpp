namespace logging {

static std::atomic<uint32_t> s_allocator_init_count(0);

static FixedSizePool* s_allocator_mem_pool = nullptr;

void initialize_allocator()
{
	if (++s_allocator_init_count != 1) return;

	assert(s_allocator_mem_pool == nullptr);
	s_allocator_mem_pool = new FixedSizePool(128, 16348);
}

void deinitialize_allocator()
{
	if (--s_allocator_init_count != 0) return;

	delete s_allocator_mem_pool;
	s_allocator_mem_pool = nullptr;
}

void* logging_allocate(std::size_t size)
{
	void* ptr = nullptr;

	assert(s_allocator_mem_pool);

	ptr = s_allocator_mem_pool->allocate(size);

	if (ptr == nullptr) {
		ptr = ::operator new(size);
		LOGGING_DEBUG("logging allocator allocated (%d) bytes using global new\n", size);
	} else {
		LOGGING_DEBUG("logging allocator allocated (%d) bytes using pool\n", size);
		LOGGING_DEBUG("log pool available %d\n", s_allocator_mem_pool->available());
	}
	return ptr;
}

void logging_deallocate(void* ptr)
{
	if (s_allocator_mem_pool->is_from(ptr)) {
		LOGGING_DEBUG("log deallocating using mem pool, available %d\n",
		              s_allocator_mem_pool->available());
		s_allocator_mem_pool->deallocate(ptr);
	} else {
		LOGGING_DEBUG("log deallocating using global delete\n");
		::operator delete(ptr);
	}
}

} // namespace logging
