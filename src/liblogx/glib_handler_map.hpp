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

#ifndef LOGX_GLIB_HANDLER_MAP_HEADER
#define LOGX_GLIB_HANDLER_MAP_HEADER

#include <map>

#include <liblogx/uncopyable.hpp>

#include <glib.h>

namespace logx {

namespace Glib {

// forward declarations
class Handler;

class HandlerMap : Uncopyable
{
public:

	/**
	 * Access to the one HandlerMap instance. I'm
	 * not thrilled about the Singleton pattern in general
	 * but GLib also has one map/list so I think it
	 * makes sense in this case.
	 */
	static HandlerMap& instance();

	/**
	 * Set a Handler to recieve a message when a log message
	 * arrives matching the particular Log domain and level/s
	 * of the Handler. I'm using the terms set and remove 
	 * here because that is what GLib uses. "set" in this 
	 * case means "add" as in that previous handlers with 
	 * the same log_domain and identical log level flags will 
	 * not be replaced by handler.
	 *
	 * XXX check that above is true.
	 */
	void set_handler(Handler* const handler);

	/**
	 * Remove a handler for a particular Log domain.
	 */
	void remove_handler(Handler* const handler);

private:

	/// Singleton....ugh.
	HandlerMap();

	/// Constructor and destructor needed for GMutex.
	~HandlerMap();

	static HandlerMap*	s_m_instance;

	/// The map type which maps LogHandlers to the identifier
	/// returned by g_log_set_handler
	typedef std::map<Handler*, unsigned int> HandlerMapType;
	
	HandlerMapType		m_map;
	GMutex*			m_gmutex;

	/**
	 * The static handler that is registered with the
	 * GLib message logging system as a callback that
	 * recieves all the log messages that match one of
	 * the LogHandler's that were registered.
	 */
	static void log_handler
		(
		 const gchar *log_domain,
		 GLogLevelFlags log_level,
		 const gchar *message,
		 gpointer log_handler_map
		);

};

} // namespace Glib

} // namespace logx

#endif // LOGX_GLIB_HANDLER_MAP_HEADER
