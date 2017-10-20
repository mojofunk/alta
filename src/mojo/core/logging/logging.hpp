#ifndef MOJO_LOGGING_H
#define MOJO_LOGGING_H

namespace logging
{

MOJO_API void
initialize();

MOJO_API void
deinitialize();

MOJO_API void
add_sink(Sink* sink_ptr);

MOJO_API void
remove_sink(Sink* sink_ptr);

MOJO_API void
write_record(Record* record);

MOJO_API Logger*
get_logger(const char* const domain);

MOJO_API std::set<Logger*>
get_loggers();

MOJO_API void
register_thread_name(const char* const thread_name);

MOJO_API void
deregister_thread_name();

MOJO_API String
thread_name(std::thread::id const& thread_id);

} // namespace logging

#endif // MOJO_LOGGING_H
