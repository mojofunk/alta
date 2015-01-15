#ifndef MOJO_APPLICATION_DATA
#define MOJO_APPLICATION_DATA

#include "mojo/core/functor_dispatcher.hpp"

#include "typedefs.hpp"

#include <glibmm/thread.h>

namespace mojo {

namespace internal {
	
struct ApplicationData
{
	ProjectSPSet projects;

	Project* active_project;

	FunctorDispatcher worker;

	Glib::Thread* worker_thread;

	// going to need a per project lock for access to
	// project data from worker thread and from client
	// when data is needed syncronously.

	// transport data
	// position and record status are properties of a project

	float speed;
	count_t position;
	bool record;

	ModuleSPSet               m_modules;

};

} // namespace internal

} // namespace mojo

#endif
