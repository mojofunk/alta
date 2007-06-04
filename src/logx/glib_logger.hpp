/*
 * Copyright (C) 2006 Tim Mayberry
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */

#ifndef LOGX_GLIB_LOGGER_HEADER
#define LOGX_GLIB_LOGGER_HEADER

#include <vector>
#include <string>
#include <sstream>

#include <logx/uncopyable.hpp>
#include <logx/glib_log_level_flags.hpp>
#include <logx/log_data_types.hpp>

namespace logx {

using std::string;
using std::ostringstream;
using std::vector;

namespace Glib {

/**
 * When I changed the name of this class from Log to Logger
 * I went looking online and found that java has a class of 
 * the same name an a bunch of very similar classes, so I'm 
 * using some of the same names where it makes sense.
 */
template <class FormatterT>
class Logger : Uncopyable {
public:

	/**
	 * Create a new Logger, a reference to the
	 * log_data is held and then passed to the logging
	 * function in the destructor.
	 */
	Logger(const char* log_domain,
			const LogLevelFlags flags)
		:
			m_domain(log_domain),
			m_flags(flags)
	{ }

	/**
	 * The Logger will add the log data to the log when
	 * the Logger is destroyed.
	 */
	~Logger()
	{
		ostringstream	osstr;
		FormatterT              formatter(m_log_data);
	
		// format the log data
		osstr << formatter;

		g_log
			(
			 m_domain,
			 (GLogLevelFlags)m_flags,
			 osstr.str().c_str()
			);
	}

	/**
	 * \brief Add some data to the log.
	 *
	 */
	template<class T> Logger& operator<<(const T& data)
	{
		ostringstream osstr;

		osstr << data;

		m_log_data.push_back(osstr.str());

		return *this;
	}

private:
	
	const char* const                       m_domain;
	const LogLevelFlags                     m_flags;

	vector<string>                m_log_data;

};

} // namespace Glib

} // namespace logx

#endif // LOGX_GLIB_LOGGER_HEADER
