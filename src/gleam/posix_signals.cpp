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

#include <cstdlib> // for EXIT_SUCCESS/FAILURE

#include <glib.h>

#include <gleam/posix_signals.hpp>

namespace {

gleam::TraceMode stack_trace_mode = gleam::STACK_TRACE_QUERY;
}

namespace gleam {

TraceMode get_trace_mode()
{
	return stack_trace_mode;
}

void set_trace_mode(TraceMode mode)
{
	stack_trace_mode = mode;
}

PosixSignalHandlerFunc
signal(int sig_num, PosixSignalHandlerFunc handler, int flags)
{
	int ret;
	struct sigaction sa;
	struct sigaction osa;

	sa.sa_handler = handler;

	//  Mask all signals while handler runs to avoid re-entrancy
	//  problems.

	sigfillset(&sa.sa_mask);

	sa.sa_flags = flags;

	ret = sigaction(sig_num, &sa, &osa);

	if (ret < 0) {

		// XXX
	}

	return (PosixSignalHandlerFunc)osa.sa_handler;
}

void termination_signal_handler(int sig_num)
{
	switch (sig_num) {
		case SIGHUP:
		case SIGINT:
		case SIGQUIT:
		case SIGABRT:
		case SIGTERM:
			g_printerr("%s terminated: %s\n", g_get_prgname(), g_strsignal(sig_num));
			break;
		default:
			break;
	}

	exit(EXIT_SUCCESS);
}

void fatal_signal_handler(int sig_num)
{
	// handle SIGILL ?
	switch (sig_num) {
		case SIGBUS:
		case SIGSEGV:
		case SIGFPE:
		case SIGPIPE:
		default:
			g_printerr("%s: fatal error: %s\n", g_get_prgname(), g_strsignal(sig_num));
			switch (stack_trace_mode) {
				case STACK_TRACE_NEVER:
					break;

				case STACK_TRACE_QUERY: {
					sigset_t sigset;

					sigemptyset(&sigset);
					pthread_sigmask(SIG_SETMASK, &sigset, NULL);
					g_on_error_query(g_get_prgname());
				} break;

				case STACK_TRACE_ALWAYS: {
					sigset_t sigset;

					sigemptyset(&sigset);
					pthread_sigmask(SIG_SETMASK, &sigset, NULL);
					g_on_error_stack_trace(g_get_prgname());
				} break;
			}
			break;
	}

	exit(EXIT_FAILURE);
}

} // namespace gleam
