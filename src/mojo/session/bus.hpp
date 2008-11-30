#ifndef MOJO_BUS
#define MOJO_BUS

#include "types.hpp"

namespace mojo {

/**
 * The Bus interface is how the Session communicates
 * with clients.
 *
 * The virtual calls are made by the Session in the
 * Session thread. If the events must be processed by
 * another thread(say the GUI thread) then it is up to
 * the derived class to queue the events to be processed
 * by another thread.
 *
 */
class Bus
{
public:

	Bus();
	virtual ~Bus();

protected:

	friend class Session;

	// all the events are called from the session thread

	virtual void on_project_added (project_t) = 0;

	/**
	 * project_t handle will only remain valid until
	 * end of call.
	 */
	virtual void on_project_removed (project_t) = 0;

	virtual void on_project_saved () = 0;
};

} // namespace mojo

#endif
