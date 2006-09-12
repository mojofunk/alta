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

#include <liblogx/glib_handler_map.hpp>
#include <liblogx/glib_log_level_flags.hpp>
#include <liblogx/glib_handler.hpp>

namespace {

/**
 * Convert a gchar* to a standard string, treating NULL as an
 * empty string.
 */
const std::string
convert_const_gchar_ptr_to_string(const char* str)
{
	return (str) ? std::string(str) : std::string();
}

} // anonymous namespace


namespace logx {

namespace Glib {

HandlerMap* HandlerMap::s_m_instance = 0;

// static
HandlerMap&
HandlerMap::instance()
{
	if(!s_m_instance) {
		s_m_instance = new HandlerMap();

		if(!s_m_instance) {
			// decide whether this is a good
			// idea
			//throw std::bad_alloc ();
		}
	}

	return *s_m_instance;
}

void
HandlerMap::set_handler(Handler* const handler)
{
	
	guint log_handler_id = g_log_set_handler (
			handler->domain().c_str(),
			(GLogLevelFlags)handler->flags(),
			HandlerMap::log_handler,
			(gpointer)(this)
			);

	{
		g_mutex_lock(m_gmutex);
		m_map.insert(std::make_pair(handler, log_handler_id));
		g_mutex_unlock(m_gmutex);
	}
}

void
HandlerMap::remove_handler(Handler* const handler)
{
	g_mutex_lock(m_gmutex);

	HandlerMapType::iterator iter = m_map.find(handler);

	g_assert (iter != m_map.end());

	g_log_remove_handler (handler->domain().c_str(),
			iter->second);

	m_map.erase(iter);

	g_mutex_unlock(m_gmutex);
}

HandlerMap::HandlerMap()
	: m_gmutex(g_mutex_new())
{

}

HandlerMap::~HandlerMap()
{
	g_mutex_free(m_gmutex);
}

// static
void
HandlerMap::log_handler (const gchar *log_domain,
			GLogLevelFlags log_level,
			const gchar *message,
			gpointer log_handler_map)
{

#if 0
	cerr
		<< "HandlerMap: " << log_domain << " "
		<< "Flags: " << log_level << " "
		<< "Message: " << message << " "
		<< endl;
#endif

	HandlerMap& handler_map = HandlerMap::instance();

	g_assert(&handler_map == static_cast<HandlerMap*>(log_handler_map));

	g_mutex_lock(handler_map.m_gmutex);

	for(HandlerMapType::const_iterator i = handler_map.m_map.begin();
			i != handler_map.m_map.end(); ++i)
	{
		Handler* handler = (*i).first;

		if(handler->domain() == log_domain
				&& (handler->flags() & log_level))
		{
			// can we ever get a NULL message?
			handler->on_log_message(convert_const_gchar_ptr_to_string(message));
		}
	}

	g_mutex_unlock(handler_map.m_gmutex);

}

} // namespace Glib

} // namespace logx
