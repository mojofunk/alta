
#include <glib.h>

#include <libgleam/terminate_process.hpp>

#ifdef G_OS_WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#endif

#include "debug.hpp"

namespace gleam {

void
terminate_process(int status)
{

#ifdef GLEAM_DEBUG_EXTRA
	LOG_GLEAM_DEBUG << "Terminating process";
#endif	
	
#ifdef G_OS_WIN32
	ExitProcess(status);
#else
	kill (-getpgrp(), SIGKILL);
#endif
	g_assert_not_reached();
	
	// Linux also has exit_group()
}

} // namespace gleam
