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

#ifndef LOGX_GLIB_HANDLER_HEADER
#define LOGX_GLIB_HANDLER_HEADER

#include <string>

#include <logx/uncopyable.hpp>
#include <logx/glib_log_level_flags.hpp>

namespace logx {

namespace Glib {

using std::string;

class Handler : Uncopyable
{
public:

	Handler(const string& domain,
			LogLevelFlags flags);

	virtual ~Handler();

	/**
	 * \return The log domain that this Handler is
	 * handling the messages for.
	 */
	const string&			domain() const
	{ return m_domain; }

	/**
	 * \return the log level flags for the handler.
	 */
	const LogLevelFlags		flags() const
	{ return m_flags; }

protected:

	/**
	 * on_log_message will be called by the HandlerMap when
	 * a log message matching the log_domain() and log level
	 * or log levels represented by the flags() bitmask.
	 */
	virtual void on_log_message (const string& message) = 0;

private:

	friend class HandlerMap;

	const string			m_domain;

	const LogLevelFlags		m_flags;
	
};

} // namespace Glib

} // namespace logx

#endif // LOGX_GLIB_HANDLER_HEADER
