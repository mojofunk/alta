
#include <mojo/audio_event.hpp>

namespace mojo {

void
AudioEvent::get_property (const std::string& name, boost::any& value) const
{
	Event::get_property (name, value);
}

void
AudioEvent::set_property (const std::string& name, const boost::any& value)
{

}

std::vector<std::string>
AudioEvent::get_property_names () const
{
	return Event::get_property_names();
}

} // namespace mojo
