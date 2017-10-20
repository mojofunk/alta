bool
get_min_max_avg_total(const std::vector<uint64_t>& values,
                      uint64_t& min,
                      uint64_t& max,
                      uint64_t& avg,
                      uint64_t& total)
{
	if (values.empty()) {
		return false;
	}

	total = 0;
	min = std::numeric_limits<uint64_t>::max();
	max = 0;
	avg = 0;

	for (std::vector<uint64_t>::const_iterator ci = values.begin();
	     ci != values.end();
	     ++ci) {
		total += *ci;
		min = std::min(min, *ci);
		max = std::max(max, *ci);
	}

	avg = total / values.size();
	return true;
}

std::string
timing_summary(const std::vector<uint64_t>& values)
{
	std::ostringstream oss;

	uint64_t min, max, avg, total;

	if (get_min_max_avg_total(values, min, max, avg, total)) {
		oss << "Count: " << values.size() << " Min: " << min << " Max: " << max
		    << " Avg: " << avg << " Total: " << total << std::endl;
	}
	return oss.str();
}
