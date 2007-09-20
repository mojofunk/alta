
#include <ark/export.h>

#include "archive.hpp"

#include <iostream>

using namespace std;

namespace ark {

ArchiveWriter*
DummyDescriptor::create_writer()
{
	return new DummyArchive;
}

ArchiveReader*
DummyDescriptor::create_reader()
{
	return new DummyArchive;
}

ModuleInfo
DummyDescriptor::get_info()
{
	return ModuleInfo("blah", "bloh", ArchiveFormat("", ""));
}


DummyArchive::DummyArchive()
{
	std::cerr << "DummyArchive()" << std::endl;
}

DummyArchive::~DummyArchive()
{
	std::cerr << "~DummyArchive()" << std::endl;
}

void
DummyArchive::read (const string& file_path, const TypeFactory& type_factory)
{

}

const Property
DummyArchive::get_property (const string& name)
{
	// XXX
	//return m_properties.find(name);
}


void
DummyArchive::add_property (const Property& prop)
{
	std::cerr << "DummyArchive::add_property: " << prop.name() << std::endl;

	m_properties.insert (prop); 
}

void
print_properties (const Object* obj, const TypeNameRegistry& reg)
{

	Properties props;

	obj->get_properties (props);

	std::cerr << "Properties: ";

	for (Properties::const_iterator i = props.begin(); i != props.end();)
	{
		std::cerr << "Name: " << i->name() << " ";
		std::cerr << "Type: " << reg.type_name(i->value().type());

		++i;

		if (i != props.end())
		{
			std::cerr << ", ";
		}

	}

	std::cerr << std::endl;

}

void
DummyArchive::write (const string& file_path, const TypeNameRegistry& reg)
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

ARK_CAPI void * ark_descriptor ()
{
	return new DummyDescriptor;
}


} // namespace ark
