#ifndef MOJO_SESSION_DATA
#define MOJO_SESSION_DATA

#include <mojo/mojo-internal.hpp>

#include "forward.hpp"

namespace mojo {

namespace internal {
	
struct SessionData
{
	std::set<Bus*> busses;

	//std::set<ProjectSPtr> projects;

};

} // namespace internal

} // namespace mojo

#endif
