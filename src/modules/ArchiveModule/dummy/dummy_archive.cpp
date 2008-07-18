
#include <cformat/cformat.hpp>

//#include <mojo/types.hpp>

#include <mojo/type_system.hpp>
#include <mojo/object.hpp>
#include <mojo/object_collection.hpp>

#include <iostream>
#include <fstream>

#include "dummy_archive.hpp"

namespace mojo {

using namespace std;

void
DummyArchive::read (const string& file_path, Properties& props)
{

}

void
DummyArchive::write_object(std::ostream& os, const ObjectSPtr& obj)
{
	const string type_name = TypeSystem::get_type_name(typeid(*obj));

	os << " Type: " << type_name << " ";

	Properties props;

	obj->get_properties (props);

	for (Properties::const_iterator i = props.begin();
			i != props.end();)
	{
		write_property (os, i->first, i->second);

		++i;

		if (i != props.end())
		{
			os << ", ";
		}

	}

	os << std::endl;
}

void
DummyArchive::write_object_collection(std::ostream& os, const ObjectCollection& col)
{
	for (ObjectCollection::const_iterator i = col.begin();
			i != col.end(); ++i)
	{
		write_object (os, *i);
	}
}

void
DummyArchive::write_property (std::ostream& os, const string& name, const boost::any& any_type)
{
	string type_name = TypeSystem::get_type_name(any_type.type());

	os << "Name: " << name << " Type: " << type_name << " Value: ";

	if(any_type.type() == typeid(ObjectCollection))
	{
		write_object_collection(os, boost::any_cast<ObjectCollection>(any_type));
	}
	else if(any_type.type() == typeid(std::string))
	{
		os << boost::any_cast<std::string>(any_type);
	}
	else if(any_type.type() == typeid(ObjectSPtr))
	{
		write_object(os, boost::any_cast<ObjectSPtr>(any_type));
	}
	else if(any_type.type() == typeid(int64_t))
	{
		os << cformat::convert<std::string>(boost::any_cast<int64_t>(any_type));
	}
	else if(any_type.type() == typeid(int32_t))
	{
		os << cformat::convert<std::string>(boost::any_cast<int32_t>(any_type));
	}
	else if(any_type.type() == typeid(float))
	{
		os << cformat::convert<std::string>(boost::any_cast<float>(any_type));
	}
}

void
DummyArchive::write (const string& file_path, const Properties& props)
{
	std::ofstream output_file (file_path.c_str());

	for (Properties::const_iterator i = props.begin();
			i != props.end(); ++i)
	{
		write_property (output_file, i->first, i->second);
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
