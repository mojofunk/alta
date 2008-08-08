
#include "event.hpp"

namespace mojo {

const char * const Event::s_property_position = "position";
const char * const Event::s_property_duration = "duration";

Event::Event () : position(0), duration(0) { }

Event::Event (const count_t& pos, const count_t& dur)
	:
		position(pos), duration(dur)
{

}

void
Event::get_properties (Properties& props) const
{
	props.insert (make_property (s_property_position, position));
	props.insert (make_property (s_property_duration, duration));
}

void
Event::set_properties (const Properties& props)
{

}

} // namespace mojo
