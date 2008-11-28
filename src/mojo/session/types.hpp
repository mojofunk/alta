#ifndef MOJO_API_TYPES
#define MOJO_API_TYPES

#include <mojo/project/typedefs.hpp>

namespace mojo {

class Bus;

struct project_t
{
	ProjectWP ptr;
};

struct track_t
{
	TrackWP ptr;
};

namespace internal {

class SessionData;

} // namespace internal

};

#endif
