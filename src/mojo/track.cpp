
#include <mojo/track.hpp>

namespace mojo {

std::string Track::s_property_name = "name";

Track::Track()
	:
		m_name("unnamed")
{

}

void
Track::get_property (const std::string& name, boost::any& value) const
{
	if (name == s_property_name)
	{
		value = m_name;
	}
}

void
Track::set_property (const std::string& name, const boost::any& value)
{

}

std::vector<std::string>
Track::get_property_names () const
{
	std::vector<std::string> property_names;

	property_names.push_back (s_property_name);

	return property_names;
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
