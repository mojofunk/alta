namespace
{

const char* const property_name = "name";
}

PropertyID const Track::s_property_name_id =
    g_quark_from_static_string(property_name);

Track::Track()
    : m_name("unnamed")
{
}

void
Track::get_properties(Properties& props) const
{
	props.set_property(s_property_name_id, m_name);
}

void
Track::set_properties(const Properties& props)
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
	Change name_change(s_property_name_id, m_name);

	if (m_name != new_name) {
		m_name = new_name;
		name_change.set_new_value(m_name);
		signal_changes(name_change);
	}
}
