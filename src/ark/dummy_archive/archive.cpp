
#include <ark/type_system.hpp>

#include <iostream>

#include "archive.hpp"

using namespace std;
using namespace ark;

DummyArchive::DummyArchive()
{
	std::cerr << "DummyArchive()" << std::endl;
}

DummyArchive::~DummyArchive()
{
	std::cerr << "~DummyArchive()" << std::endl;
}

void
DummyArchive::read (const string& file_path)
{

}

const Property
DummyArchive::get_property (const string& name)
{
	// XXX
	//return m_properties.find(name);
}


void
DummyArchive::set_property (const Property& prop)
{
	std::cerr << "DummyArchive::add_property: " << prop.name() << std::endl;

	m_properties.insert (prop); 
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

	// recursively find all the Properties that are of type ark::Object
	// and put them into a map<Object*, uint64_t> where each object is
	// assigned a unique id.

	// check that the TypeNameRegistry has an name for each property type in
	// the archive

	// work out if all the types are supported by this archive.

	// write all non ark::Object properties to the archive





}
