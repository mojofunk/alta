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

#ifndef GLEAM_POSIX_SIGNALS_INCLUDED
#define GLEAM_POSIX_SIGNALS_INCLUDED

#include <signal.h>

namespace gleam {

	enum TraceMode {
		STACK_TRACE_NEVER,
		STACK_TRACE_QUERY,
		STACK_TRACE_ALWAYS
	};

	TraceMode get_trace_mode();

	void set_trace_mode(TraceMode mode);

	typedef void (* PosixSignalHandlerFunc) (int sig_num);
		
	PosixSignalHandlerFunc signal (int sig_num, PosixSignalHandlerFunc, int flags);

	void termination_signal_handler (int sig_num);

	void fatal_signal_handler (int sig_num);

} // namespace gleam

#endif // GLEAM_POSIX_SIGNALS_INCLUDED
