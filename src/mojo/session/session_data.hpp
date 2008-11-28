#ifndef MOJO_SESSION_DATA
#define MOJO_SESSION_DATA

#include "types.hpp"

namespace mojo {

namespace internal {
	
struct SessionData
{
	std::set<Bus*> busses;

	//std::set<ProjectSP> projects;

};

} // namespace internal

} // namespace mojo

#endif
