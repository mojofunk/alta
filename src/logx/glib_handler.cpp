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

#include <logx/glib_handler.hpp>
#include <logx/glib_handler_map.hpp>

namespace logx {

namespace Glib {

Handler::Handler (const std::string& log_domain,
			LogLevelFlags log_flags)
	:
		m_domain(log_domain),
		m_flags(log_flags)
{
	HandlerMap::instance().set_handler(this);
}

Handler::~Handler ()
{
	HandlerMap::instance().remove_handler(this);
}

} // namespace Glib

} // namespace logx
