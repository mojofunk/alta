
#ifndef MOJO_DEBUG_INCLUDED
#define MOJO_DEBUG_INCLUDED

#if defined(NDEBUG) || defined(MOJO_NDEBUG)
// Don't define MOJO_DEBUG 
#else
#define MOJO_DEBUG
#endif

/*
 * If MOJO_DEBUG is not defined, then do absolutely nothing.
 */
#ifdef MOJO_DEBUG

#include <logx.hpp>

#include <libgleam/thread_debug.hpp>

#include "log_domain.hpp"

/*
 * Define the default log types available when MOJO_DEBUG is
 * defined/enabled.
 */
#define LOG_MOJO_ERROR logx::Glib::Logger<logx::PrettyFormatter>(mojo::log_domain, logx::Glib::ERROR) \
	<< logx::ThreadIdentifier(gleam::thread_map().current_thread_name()) \
	<< logx::FileIdentifier(__FILE__) \
	<< logx::LineIdentifier(__LINE__) \
	<< logx::FunctionIdentifier(G_STRFUNC)

#define LOG_MOJO_CRITICAL logx::Glib::Logger<logx::PrettyFormatter>(mojo::log_domain, logx::Glib::CRITICAL) \
	<< logx::ThreadIdentifier(gleam::thread_map().current_thread_name()) \
	<< logx::FileIdentifier(__FILE__) \
	<< logx::LineIdentifier(__LINE__) \
	<< logx::FunctionIdentifier(G_STRFUNC)

#define LOG_MOJO_WARNING logx::Glib::Logger<logx::PrettyFormatter>(mojo::log_domain, logx::Glib::WARNING) \
	<< logx::ThreadIdentifier(gleam::thread_map().current_thread_name()) \
	<< logx::FileIdentifier(__FILE__) \
	<< logx::LineIdentifier(__LINE__) \
	<< logx::FunctionIdentifier(G_STRFUNC)


#if defined(NDEBUG_EXTRA) || defined(MOJO_NDEBUG_EXTRA)
// don't generate extra debugging information
#else
#define MOJO_DEBUG_EXTRA
#endif

/*
 * Define the Log for extra debugging output if enabled.
 */
#ifdef MOJO_DEBUG_EXTRA

#define LOG_MOJO_DEBUG logx::Glib::Logger<logx::PrettyFormatter>(mojo::log_domain, logx::Glib::DEBUG) \
	<< logx::ThreadIdentifier(gleam::thread_map().current_thread_name()) \
	<< logx::FileIdentifier(__FILE__) \
	<< logx::LineIdentifier(__LINE__) \
	<< logx::FunctionIdentifier(G_STRFUNC)

#endif // MOJO_DEBUG_EXTRA

#endif // MOJO_DEBUG

#endif // MOJO_DEBUG_INCLUDED
