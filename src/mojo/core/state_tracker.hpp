
#ifndef MOJO_STATE_TRACKER
#define MOJO_STATE_TRACKER

#include "object.hpp"

namespace mojo {

/**
 * The StateTracker class monitors Objects for property changes
 * and then stores the property changes in an Archive
 */
class StateTracker : public Object
{
public:

	StateTracker ();

public:

	virtual void get_properties (Properties& props) const;

	virtual void set_properties (const Properties& props);

private:

};

} // namespace mojo

#endif
