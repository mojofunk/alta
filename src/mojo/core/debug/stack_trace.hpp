#ifndef MOJO_CORE_STACK_TRACE_H
#define MOJO_CORE_STACK_TRACE_H

class MOJO_API StackTrace {
public:
	/**
	 * Creates a stack trace at the current location
	 */
	StackTrace();

	/**
	 * Get addresses contained in stacktrace
	 * @return addresses or NULL
	 * @param count number of elements/addresses in returned array
	 */
	const void* const* get_addresses(size_t& count) const;

	/**
	 * print stacktrace to stderr
	 * @param start_offset stack frames to offset output
	 */
	void print(size_t start_offset = 0) const;

	/**
	 * @param os stream to output stacktrace
	 * @param start_offset stack frames to offset output
	 */
	void to_stream(std::ostream& os, size_t start_offset = 0) const;

	/**
	 * @param start_offset stack frames to offset output
	 * @return string containing stacktrace
	 */
	std::string to_string(size_t start_offset = 0) const;

	/**
	 * @return true if stacktraces are equivalent
	 *
	 * This compares all the frame addresses in the stack
	 */
	bool operator==(const StackTrace& other)
	{
		if (m_count != other.m_count) return false;

		for (size_t i = 0; i < m_count; ++i) {
			if (m_trace[i] != other.m_trace[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(const StackTrace& other) { return !operator==(other); }

private:
	static const int s_max_traces = 62;

	void* m_trace[s_max_traces];

	size_t m_count;
};

#endif // MOJO_CORE_STACK_TRACE_H
