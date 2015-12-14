#ifndef MOJO_LOGGING_MACROS_H
#define MOJO_LOGGING_MACROS_H

#define M_DECLARE_LOGGER(Name) extern std::shared_ptr<logging::Logger> Name;

#define M_DEFINE_LOGGER(Name) std::shared_ptr<logging::Logger> Name;

#define M_LOG(Logger, Message)                                                 \
	Logger->write_record(Message,                                                 \
	                     logging::thread_name(),                                  \
	                     logging::TimeStamp::get_microseconds(),                  \
	                     __LINE__,                                                \
	                     __FILE__,                                                \
	                     M_STRFUNC);

#define M_LOG_CALL(Logger)                                                     \
	Logger->write_record("Timestamp",                                             \
	                     logging::thread_name(),                                  \
	                     logging::TimeStamp::get_microseconds(),                  \
	                     __LINE__,                                                \
	                     __FILE__,                                                \
	                     M_STRFUNC);

#endif // MOJO_LOGGING_MACROS_H
