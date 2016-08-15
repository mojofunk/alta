uint32_t get_cpu_id()
{
#ifdef MOJO_LINUX
	return sched_getcpu();
#elif MOJO_WINDOWS
	return GetCurrentProcessorNumber();
#endif
	return 0;
}
