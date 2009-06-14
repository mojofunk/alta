#ifndef MOJO_SESSION_DATA
#define MOJO_SESSION_DATA

#include <mojo/mojo-internal.hpp>

#include "session_worker.hpp"

#include <glibmm/thread.h>

namespace mojo {

namespace internal {
	
struct SessionData
{
	std::set<SessionBus*> busses;

	std::set<ProjectSP> projects;

	SessionWorker worker;

	Glib::Thread* worker_thread;

};

} // namespace internal

} // namespace mojo

#endif
