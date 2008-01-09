
#include <mojo/type_system.hpp>

#include <iostream>

#include <mojo/dummy_archive.hpp>

namespace mojo {

using namespace std;

void
DummyArchive::read (const string& file_path)
{

}

void
DummyArchive::get_property (const string& name, boost::any& value)
{
	Properties::const_iterator i = m_properties.find(name);

	if(i != m_properties.end()) value = i->second;
}


void
DummyArchive::set_property (const string& name, const boost::any& value)
{
	m_properties.insert (make_pair (name, value)); 
}

#if 0
void
print_properties (const Object* obj)
{

	Properties props;

	obj->get_properties (props);

	std::cerr << "Properties: ";

	for (Properties::const_iterator i = props.begin(); i != props.end();)
	{
		std::cerr << "Name: " << i->name() << " ";
		std::cerr << "Type: " << get_type_name(i->value().type());

		++i;

		if (i != props.end())
		{
			std::cerr << ", ";
		}

	}

	std::cerr << std::endl;

}

#endif

void
DummyArchive::write (const string& file_path)
{
	std::cerr << "DummyArchive::write "  << file_path << std::endl;

	for (Properties::const_iterator i = m_properties.begin();
			i != m_properties.end(); ++i)
	{
		std::cerr << "Property: " << i->first
			<< " Type: " << TypeSystem::get_type_name(i->second.type())
			<< std::endl;
	}

	// recursively find all the Properties that are of type mojo::Object
	// and put them into a map<Object*, uint64_t> where each object is
	// assigned a unique id.

	// check that the TypeNameRegistry has an name for each property type in
	// the archive

	// work out if all the types are supported by this archive.

	// write all non mojo::Object properties to the archive

}

} // namespace mojo
