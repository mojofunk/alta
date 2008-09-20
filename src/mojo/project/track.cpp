
#include "track.hpp"

namespace mojo {

const char * const Track::s_property_name = "name";

Track::Track()
	:
		m_name("unnamed")
{

}

void
Track::get_properties (Properties& props) const
{
	props.insert (make_property (s_property_name, m_name));
}

void
Track::set_properties (const Properties& props)
{

}

std::string
Track::get_name() const
{
	return m_name;
}

void
Track::set_name(const std::string& new_name)
{
	if (m_name != new_name)
	{
		m_name = new_name;
	}
}

} // namespace mojo
