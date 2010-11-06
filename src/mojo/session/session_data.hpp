#ifndef MOJO_SESSION_DATA
#define MOJO_SESSION_DATA

#include <mojo/mojo-internal.hpp>

#include "session_worker.hpp"

#include <glibmm/thread.h>

namespace mojo {

namespace internal {
	
struct SessionData
{
	std::set<SessionEventHandler*> event_handlers;

	std::set<ProjectSP> projects;

	Project* active_project;

	SessionWorker worker;

	Glib::Thread* worker_thread;

	// transport data
	// position and record status are properties of a project

	float speed;
	count_t position;
	bool record;

};

} // namespace internal

} // namespace mojo

#endif
