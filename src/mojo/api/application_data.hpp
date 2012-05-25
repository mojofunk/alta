#ifndef MOJO_APPLICATION_DATA
#define MOJO_APPLICATION_DATA

#include "mojo-internal.hpp"

#include "application_worker.hpp"

#include <glibmm/thread.h>

namespace mojo {

namespace internal {
	
struct ApplicationData
{
	std::set<ApplicationEventHandler*> event_handlers;

	std::set<ProjectSP> projects;

	Project* active_project;

	ApplicationWorker worker;

	Glib::Thread* worker_thread;

	// going to need a per project lock for access to
	// project data from worker thread and from client
	// when data is needed syncronously.

	// transport data
	// position and record status are properties of a project

	float speed;
	count_t position;
	bool record;

};

} // namespace internal

} // namespace mojo

#endif
