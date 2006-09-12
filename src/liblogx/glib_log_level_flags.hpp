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

#ifndef LOGX_GLIB_LOG_LEVEL_FLAGS_HEADER
#define LOGX_GLIB_LOG_LEVEL_FLAGS_HEADER

// this is defined on WIN32 for reasons yet to
// be determined.
#ifdef ERROR
#undef ERROR
#endif

namespace logx {

namespace Glib {

/**
 * This enum corresponds to the enum that is
 * defined by the GLib message logging system
 *
 * http://developer.gnome.org/doc/API/2.0/glib/glib-Message-Logging.html
 *
 * How the different levels are used is left up
 * to the user but there is a certain convention
 * that is widely followed which is roughly:
 *
 */
enum LogLevelFlags {
	RECURSION = 1 << 0,
	FATAL = 1 << 1,

	/**
	 * The error message log level is always fatal and
	 * will terminate the running process.
	 */
	ERROR = 1 << 2, 
	
	/**
	 * The critical message log level is for critical 
	 * log messages. The G_DEBUG environment variable
	 * can be used to control certain aspects of the 
	 * GLib system, including making all critical log
	 * messages fatal.
	 */
	CRITICAL = 1 << 3,
	WARNING = 1 << 4,
	MESSAGE = 1 << 5,
	INFO = 1 << 6,
	DEBUG = 1 << 7
};

inline LogLevelFlags operator|(LogLevelFlags lhs, LogLevelFlags rhs)
  { return static_cast<LogLevelFlags>(static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs)); }

inline LogLevelFlags operator&(LogLevelFlags lhs, LogLevelFlags rhs)
  { return static_cast<LogLevelFlags>(static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs)); }

inline LogLevelFlags operator^(LogLevelFlags lhs, LogLevelFlags rhs)
  { return static_cast<LogLevelFlags>(static_cast<unsigned>(lhs) ^ static_cast<unsigned>(rhs)); }

inline LogLevelFlags operator~(LogLevelFlags flags)
  { return static_cast<LogLevelFlags>(~static_cast<unsigned>(flags)); }

inline LogLevelFlags& operator|=(LogLevelFlags& lhs, LogLevelFlags rhs)
  { return (lhs = static_cast<LogLevelFlags>(static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs))); }

inline LogLevelFlags& operator&=(LogLevelFlags& lhs, LogLevelFlags rhs)
  { return (lhs = static_cast<LogLevelFlags>(static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs))); }

inline LogLevelFlags& operator^=(LogLevelFlags& lhs, LogLevelFlags rhs)
  { return (lhs = static_cast<LogLevelFlags>(static_cast<unsigned>(lhs) ^ static_cast<unsigned>(rhs))); }

} // namespace Glib

} // namespace logx

#endif // LOGX_GLIB_LOG_LEVEL_FLAGS_HEADER
