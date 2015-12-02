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
