
#include "event.hpp"

namespace {

const char * const Event::s_property_position = "position";
const char * const Event::s_property_duration = "duration";

}

PropertyID const Event::s_property_position_id = g_quark_from_static_string (s_property_position);
PropertyID const Event::s_property_duration_id = g_quark_from_static_string (s_property_duration);

namespace mojo {

Event::Event () : position(0), duration(0) { }

Event::Event (const count_t& pos, const count_t& dur)
	:
		position(pos), duration(dur)
{

}

void
Event::get_properties (Properties& props) const
{
	props.set_property (s_property_position_id, position);
	props.set_property (s_property_duration_id, duration);
}

void
Event::set_properties (const Properties& props)
{

}

} // namespace mojo
