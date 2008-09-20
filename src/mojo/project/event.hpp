#ifndef MOJO_EVENT
#define MOJO_EVENT

#include <mojo/core/types.hpp>

#include "object.hpp"

namespace mojo {

class Event : public Object
{
public:

	Event();

	Event(const count_t& pos, const count_t& dur);

public:

	// Object interface
	virtual void get_properties (Properties& props) const;

	virtual void set_properties (const Properties& props);

public:

	count_t		position;
	count_t		duration;

private:

	// property names
	static const char * const s_property_position;
	static const char * const s_property_duration;

};

} // namespace mojo

#endif
