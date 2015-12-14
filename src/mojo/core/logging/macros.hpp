#ifndef MOJO_LOGGING_MACROS_H
#define MOJO_LOGGING_MACROS_H

#define M_DECLARE_LOGGER(Name)                                                 \
	extern std::shared_ptr<logging::Logger>& Name_logger();

#define M_DEFINE_LOGGER(Name)                                                  \
	std::shared_ptr<logging::Logger>& Name_logger()                               \
	{                                                                             \
		static std::shared_ptr<logging::Logger> logger =                             \
		    logging::make_logger(#Name);                                             \
		return logger;                                                               \
	}

#define M_LOG(Name, Message)                                                   \
	Name_logger()->write_record(Message,                                          \
	                            logging::thread_name().c_str(),                   \
	                            logging::TimeStamp::get_microseconds(),           \
	                            __LINE__,                                         \
	                            __FILE__,                                         \
	                            M_STRFUNC);

#define M_LOG_CALL(Name)                                                       \
	Name_logger()->write_record("Timestamp",                                      \
	                            logging::thread_name().c_str(),                   \
	                            logging::TimeStamp::get_microseconds(),           \
	                            __LINE__,                                         \
	                            __FILE__,                                         \
	                            M_STRFUNC);

#endif // MOJO_LOGGING_MACROS_H
