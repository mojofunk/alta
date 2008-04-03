#include <glib.h>

#ifdef G_OS_UNIX
#include <gleam/posix_signals.hpp>
#endif

#ifdef G_OS_WIN32
#include <cstdlib>
#include <gleam/terminate_process.hpp>
#endif

#include <ui/utils/signal_handler.hpp>

namespace gmojo {

SignalHandler::SignalHandler()
{
#ifdef G_OS_UNIX
	gleam::signal (SIGHUP,  gleam::termination_signal_handler, 0);
	gleam::signal (SIGINT,  gleam::termination_signal_handler, 0);
	gleam::signal (SIGQUIT, gleam::termination_signal_handler, 0);
	
	gleam::signal (SIGBUS,  gleam::fatal_signal_handler, 0);
	gleam::signal (SIGSEGV, gleam::fatal_signal_handler, 0);
	gleam::signal (SIGTERM, gleam::fatal_signal_handler, 0);
	gleam::signal (SIGFPE,  gleam::fatal_signal_handler, 0);

	// Ignore SIGPIPE
	gleam::signal (SIGPIPE, SIG_IGN, 0);

	// Restart syscalls interrupted by SIGCHLD
	// gleam::signal (SIGCHLD, SIG_DFL, SA_RESTART);
#endif

	// Windows??
}

SignalHandler::~SignalHandler()
{
#ifdef G_OS_WIN32
	gleam::terminate_process(EXIT_SUCCESS);
#endif
}

} // namespace gmojo
