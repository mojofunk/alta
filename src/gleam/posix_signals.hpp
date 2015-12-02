#ifndef GLEAM_POSIX_SIGNALS_H
#define GLEAM_POSIX_SIGNALS_H

namespace gleam {

enum TraceMode { STACK_TRACE_NEVER, STACK_TRACE_QUERY, STACK_TRACE_ALWAYS };

TraceMode get_trace_mode();

void set_trace_mode(TraceMode mode);

typedef void (*PosixSignalHandlerFunc)(int sig_num);

PosixSignalHandlerFunc signal(int sig_num, PosixSignalHandlerFunc, int flags);

void termination_signal_handler(int sig_num);

void fatal_signal_handler(int sig_num);

} // namespace gleam

#endif // GLEAM_POSIX_SIGNALS_H
