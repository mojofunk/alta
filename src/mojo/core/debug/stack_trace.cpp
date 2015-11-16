#ifdef HAVE_EXECINFO
#include <execinfo.h>
#endif

StackTrace::StackTrace()
    : m_count(0)
{
#ifdef HAVE_EXECINFO
	m_count = backtrace(m_trace, s_max_traces);
#endif
}

const void* const* StackTrace::get_addresses(size_t& count) const
{
	count = m_count;
	if (m_count) {
		return m_trace;
	}
	return NULL;
}

void StackTrace::print(size_t start_offset) const
{
	to_stream(std::cerr, start_offset);
}

void StackTrace::to_stream(std::ostream& os, size_t start_offset) const
{
#ifdef HAVE_EXECINFO
	char** trace_lines = backtrace_symbols(m_trace, m_count);

	for (size_t i = start_offset; i < m_count; ++i) {
		std::string demangled_line = demangle(trace_lines[i]);
		os << demangled_line;
		os << std::endl;
	}

	free(trace_lines);
#endif
}

std::string StackTrace::to_string(size_t start_offset) const
{
	std::ostringstream oss;
	to_stream(oss, start_offset);
	return oss.str();
}
