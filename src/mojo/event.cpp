
#include <mojo/event.hpp>

namespace mojo {

const char * const Event::s_property_position = "position";
const char * const Event::s_property_duration = "duration";

void
Event::get_property (const std::string& name, boost::any& value) const
{
	if (name == s_property_position)
	{
		value = position;
	}
	else if (name == s_property_duration)
	{
		value = duration;
	}
}

void
Event::set_property (const std::string& name, const boost::any& value)
{

}

std::vector<std::string>
Event::get_property_names () const
{
	std::vector<std::string> property_names;

	property_names.push_back (s_property_position);
	property_names.push_back (s_property_duration);

	return property_names;
}

} // namespace mojo
