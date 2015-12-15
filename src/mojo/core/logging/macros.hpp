#ifndef MOJO_LOGGING_MACROS_H
#define MOJO_LOGGING_MACROS_H

#define M_DECLARE_LOGGER(Name) extern logging::Logger* Name##Logger

#define M_DEFINE_LOGGER(Name) logging::Logger* Name##Logger

#define M_GET_LOGGER(Name) Name##Logger = logging::get_logger(#Name)

#define M_LOG(Name, Message)                                                   \
	Name##Logger->write_record(Message,                                           \
	                           logging::thread_name(),                            \
	                           logging::TimeStamp::get_microseconds(),            \
	                           __LINE__,                                          \
	                           __FILE__,                                          \
	                           M_STRFUNC)

#define M_LOG_CALL(Name)                                                       \
	Name##Logger->write_record("Timestamp",                                       \
	                           logging::thread_name(),                            \
	                           logging::TimeStamp::get_microseconds(),            \
	                           __LINE__,                                          \
	                           __FILE__,                                          \
	                           M_STRFUNC)

#endif // MOJO_LOGGING_MACROS_H
