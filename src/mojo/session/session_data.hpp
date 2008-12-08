#ifndef MOJO_SESSION_DATA
#define MOJO_SESSION_DATA

#include <mojo/mojo-internal.hpp>

#include "session_dispatcher.hpp"

namespace mojo {

namespace internal {
	
struct SessionData
{
	std::set<Bus*> busses;

	std::set<ProjectSP> projects;

	SessionDispatcher dispatcher;
};

} // namespace internal

} // namespace mojo

#endif
