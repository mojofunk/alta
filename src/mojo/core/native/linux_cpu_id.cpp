uint32_t get_cpu_id()
{
	return sched_getcpu();
}
