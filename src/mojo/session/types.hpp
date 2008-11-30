#ifndef MOJO_API_TYPES
#define MOJO_API_TYPES

#include <mojo/project/typedefs.hpp>

namespace mojo {

class Bus;

class project_t
{
public:

	project_t () { }

	void reset () { ptr.reset(); }

	void operator=(const project_t& p)
	{
		ptr = p.ptr;
	}

	bool operator==(const project_t& p)
	{
		// is this ok?
		return (ptr.lock().get() == p.ptr.lock().get());
	}

private:
	friend class Session;
	project_t (const ProjectSP& sp) : ptr(sp) { }
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
