#ifndef MOJO_SESSION_DATA
#define MOJO_SESSION_DATA


#include "types.hpp"
#include "queue.hpp"

namespace mojo {

namespace internal {
	
struct SessionData
{
	std::set<Bus*> busses;

	std::set<ProjectSP> projects;

	Queue queue;

};

} // namespace internal

} // namespace mojo

#endif
