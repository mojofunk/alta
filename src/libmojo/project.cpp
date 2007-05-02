
#include "project.hpp"

namespace mojo {

boost::shared_ptr<Project>
Project::create()
{
	boost::shared_ptr<Project> ptr(new Project, Project::deleter());
	return ptr;
}

Project::Project ()
{


}

Project::~Project()
{


}

void
Project::set_name (const std::string& new_name)
{
	m_name = new_name;
}

const std::string&
Project::get_name () const
{
	return m_name;
}

} // namespace mojo
