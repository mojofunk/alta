namespace logging {

void* Record::operator new(size_t size)
{
	// TODO use a pool instead as size is known/fixed
	return logging_allocate(size);
}

void Record::operator delete(void* ptr)
{
	logging_deallocate(ptr);
}

} // namespace logging
