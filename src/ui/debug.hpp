
#ifndef GMOJO_DEBUG_INCLUDED
#define GMOJO_DEBUG_INCLUDED

#if defined(NDEBUG) || defined(GMOJO_NDEBUG)
// Don't define GMOJO_DEBUG 
#else
#define GMOJO_DEBUG
#endif

/*
 * If GMOJO_DEBUG is not defined, then do absolutely nothing.
 */
#ifdef GMOJO_DEBUG

#include <logx.hpp>

#include <libgleam/thread_debug.hpp>

#include "log_domain.hpp"
#include "thread_names.hpp"

/*
 * Define the default log types available when GMOJO_DEBUG is
 * defined/enabled.
 */
#define LOG_GMOJO_ERROR logx::Glib::Logger<logx::PrettyFormatter>(gmojo::log_domain, logx::Glib::ERROR) \
	<< logx::ThreadIdentifier(gleam::thread_map().current_thread_name()) \
	<< logx::FileIdentifier(__FILE__) \
	<< logx::LineIdentifier(__LINE__) \
	<< logx::FunctionIdentifier(G_STRFUNC)

#define LOG_GMOJO_CRITICAL logx::Glib::Logger<logx::PrettyFormatter>(gmojo::log_domain, logx::Glib::CRITICAL) \
	<< logx::ThreadIdentifier(gleam::thread_map().current_thread_name()) \
	<< logx::FileIdentifier(__FILE__) \
	<< logx::LineIdentifier(__LINE__) \
	<< logx::FunctionIdentifier(G_STRFUNC)

#define LOG_GMOJO_WARNING logx::Glib::Logger<logx::PrettyFormatter>(gmojo::log_domain, logx::Glib::WARNING) \
	<< logx::ThreadIdentifier(gleam::thread_map().current_thread_name()) \
	<< logx::FileIdentifier(__FILE__) \
	<< logx::LineIdentifier(__LINE__) \
	<< logx::FunctionIdentifier(G_STRFUNC)


#if defined(NDEBUG_EXTRA) || defined(GMOJO_NDEBUG_EXTRA)
// don't generate extra debugging information
#else
#define GMOJO_DEBUG_EXTRA
#endif

/*
 * Define the Log for extra debugging output if enabled.
 */
#ifdef GMOJO_DEBUG_EXTRA

#define LOG_GMOJO_DEBUG logx::Glib::Logger<logx::PrettyFormatter>(gmojo::log_domain, logx::Glib::DEBUG) \
	<< logx::ThreadIdentifier(gleam::thread_map().current_thread_name()) \
	<< logx::FileIdentifier(__FILE__) \
	<< logx::LineIdentifier(__LINE__) \
	<< logx::FunctionIdentifier(G_STRFUNC)

#endif // GMOJO_DEBUG_EXTRA

#endif // GMOJO_DEBUG

#endif // GMOJO_DEBUG_INCLUDED
