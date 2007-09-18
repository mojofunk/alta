
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

const Object*
DummyArchive::get_object (const string& name)
{
	// XXX
	return m_objects.find(name)->second;
}


void
DummyArchive::add_object (const string& name, const Object* obj)
{
	std::cerr << "DummyArchive::add_object " << name << std::endl;

	m_objects.insert (std::make_pair (name, obj)); 
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
		std::cerr << "Value: " << reg.type_name(i->value().type());

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

	for (ObjectMap::const_iterator i = m_objects.begin(); i != m_objects.end(); ++i)
	{
		std::cerr << "Name: " << i->first << std::endl;

		print_properties (i->second, reg);

	}



}

ARK_CAPI void * ark_descriptor ()
{
	return new DummyDescriptor;
}


} // namespace ark
