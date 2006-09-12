/*
   Copyright (C) 2006 Tim Mayberry

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA  02110-1301, USA.
*/

#ifndef GLEAM_DEBUG_INCLUDED
#define GLEAM_DEBUG_INCLUDED

#if defined(NDEBUG) || defined(GLEAM_NDEBUG)
// Don't define GLEAM_DEBUG 
#else
#define GLEAM_DEBUG
#endif

/*
 * If GLEAM_DEBUG is not defined, then do absolutely nothing.
 */
#ifdef GLEAM_DEBUG

#include <logx.hpp>

#include <libgleam/log_domain.hpp>
#include <libgleam/thread_debug.hpp>

/*
 * Define the default log types available when GLEAM_DEBUG is
 * defined/enabled.
 */
#define LOG_GLEAM_ERROR logx::Glib::Logger<logx::PrettyFormatter>(gleam::log_domain, logx::Glib::ERROR) \
	<< logx::ThreadIdentifier(gleam::thread_map().current_thread_name()) \
	<< logx::FileIdentifier(__FILE__) \
	<< logx::LineIdentifier(__LINE__) \
	<< logx::FunctionIdentifier(G_STRFUNC)

#define LOG_GLEAM_CRITICAL logx::Glib::Logger<logx::PrettyFormatter>(gleam::log_domain, logx::Glib::CRITICAL) \
	<< logx::ThreadIdentifier(gleam::thread_map().current_thread_name()) \
	<< logx::FileIdentifier(__FILE__) \
	<< logx::LineIdentifier(__LINE__) \
	<< logx::FunctionIdentifier(G_STRFUNC)

#define LOG_GLEAM_WARNING logx::Glib::Logger<logx::PrettyFormatter>(gleam::log_domain, logx::Glib::WARNING) \
	<< logx::ThreadIdentifier(gleam::thread_map().current_thread_name()) \
	<< logx::FileIdentifier(__FILE__) \
	<< logx::LineIdentifier(__LINE__) \
	<< logx::FunctionIdentifier(G_STRFUNC)


#if defined(NDEBUG_EXTRA) || defined(GLEAM_NDEBUG_EXTRA)
// don't generate extra debugging information
#else
#define GLEAM_DEBUG_EXTRA
#endif

/*
 * Define the Log for extra debugging output if enabled.
 */
#ifdef GLEAM_DEBUG_EXTRA

#define LOG_GLEAM_DEBUG logx::Glib::Logger<logx::PrettyFormatter>(gleam::log_domain, logx::Glib::DEBUG) \
	<< logx::ThreadIdentifier(gleam::thread_map().current_thread_name()) \
	<< logx::FileIdentifier(__FILE__) \
	<< logx::LineIdentifier(__LINE__) \
	<< logx::FunctionIdentifier(G_STRFUNC)

#endif // GLEAM_DEBUG_EXTRA

#endif // GLEAM_DEBUG

#endif // GLEAM_DEBUG_INCLUDED
