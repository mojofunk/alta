#ifndef MOJO_STATE_TRACKER_H
#define MOJO_STATE_TRACKER_H

#ifndef MOJO_APPLICATION_AMALGAMATED
#include "mojo/core/object/object.hpp"
#endif

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

#endif // MOJO_STATE_TRACKER_H
