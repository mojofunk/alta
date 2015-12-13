#ifndef MOJO_LOGGING_RECORD_H
#define MOJO_LOGGING_RECORD_H

namespace logging {

struct Record {
	Record(const String& p_message,
	          const char* const p_logger_name,
	          const String& p_thread_name,
	          uint64_t p_timestamp,
	          int p_line,
	          const char* const p_file_name,
	          const char* const p_function_name)
	    : message(p_message)
	    , logger_name(p_logger_name)
	    , thread_name(p_thread_name)
	    , timestamp(p_timestamp)
	    , line(p_line)
	    , file_name(p_file_name)
	    , function_name(p_function_name)
	{
	}

	const String message;

	const String logger_name;

	const String thread_name;

	const uint64_t timestamp;

	const int line;

	// copy these as if a dll that contains a Logger and is
	// unloaded the addresses will be invalid...perf impact?
	const String file_name;
	const String function_name;

public: // class new/delete
	void* operator new(size_t size);

	void operator delete(void* ptr);

private:
	M_DISALLOW_COPY_AND_ASSIGN(Record);
};

} // namespace logging

#endif // MOJO_LOGGING_RECORD_H
