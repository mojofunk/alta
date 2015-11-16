namespace mojo {

uint64_t get_monotonic_time()
{
	using namespace std::chrono;
	auto duration = high_resolution_clock::now();
	return duration_cast<microseconds>(duration.time_since_epoch()).count();
}

void usleep(uint64_t microseconds)
{
	g_usleep(microseconds);
}

void sleep(uint32_t seconds)
{
	g_usleep(seconds * 1000000);
}

} // namespace mojo
