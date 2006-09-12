#ifndef LOGX_LOGGER_HEADER
#define LOGX_LOGGER_HEADER

#include <liblogx/uncopyable.hpp>
#include <liblogx/glib_log_level_flags.hpp>
#include <liblogx/log_handler_map.hpp>

namespace logx {

class Logger : Uncopyable
{
public:

	Logger(const char* const log_domain,
			const flags_type flags)
		:
			m_domain(log_domain),
			m_flags(flags)
	{ }

	~Logger()
	{
		LogHandlerMap::instance().log(m_domain, m_flags, m_log_data);
	}

	template<class T> Logger& operator<<(const T& data)
	{
		// create_log_data will allocate.
		m_log_data.push_back(create_log_data(data));

		return *this;
	}

private:
	
	const char* const                   m_domain;
	const LogLevelFlags                 m_flags;

	vector<LogData*>                    m_log_data;


};

} // namespace logx

#endif // LOGX_LOGGER_HEADER
