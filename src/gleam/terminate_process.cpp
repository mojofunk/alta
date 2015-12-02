namespace gleam {

void terminate_process(int status)
{
#ifdef G_OS_WIN32
	ExitProcess(status);
#else
	kill(-getpgrp(), SIGKILL);
#endif
	g_assert_not_reached();

	// Linux also has exit_group()
}

} // namespace gleam
