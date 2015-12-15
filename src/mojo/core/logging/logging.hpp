#ifndef MOJO_LOGGING_H
#define MOJO_LOGGING_H

namespace logging {

MOJO_API void initialize();

MOJO_API void deinitialize();

MOJO_API void add_sink(std::shared_ptr<Sink> sink_ptr);

MOJO_API void remove_sink(std::shared_ptr<Sink> sink_ptr);

MOJO_API void write_record(Record* record);

MOJO_API std::shared_ptr<Logger> make_logger(const char* const logging_domain);

MOJO_API std::set<std::shared_ptr<Logger>> get_loggers();

MOJO_API void register_thread_name(const char* const thread_name);

MOJO_API void deregister_thread_name();

MOJO_API String thread_name();

} // namespace logging

#endif // MOJO_LOGGING_H
