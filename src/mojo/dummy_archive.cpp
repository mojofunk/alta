
#include <mojo/type_system.hpp>
#include <mojo/object.hpp>
#include <mojo/object_collection.hpp>

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

void
print_object_properties(const ObjectSPtr& obj)
{
	const string type_name = TypeSystem::get_type_name(typeid(*obj));

	std::cerr << " type: " << type_name;

	vector<string> prop_names = obj->get_property_names ();

	std::cerr << " Properties: ";

	for (vector<string>::const_iterator i = prop_names.begin();
			i != prop_names.end();)
	{
		boost::any prop;
		obj->get_property(*i, prop);
		string type_name = TypeSystem::get_type_name(prop.type());

		std::cerr << "Name: " << *i << " ";
		std::cerr << "Type: " << type_name;

		++i;

		if (i != prop_names.end())
		{
			std::cerr << ", ";
		}

	}

	std::cerr << std::endl;
}

void
print_object_collection(const ObjectCollection& col)
{
	for (ObjectCollection::const_iterator i = col.begin();
			i != col.end(); ++i)
	{
		print_object_properties (*i);
	}
}

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

		ObjectCollection collection = boost::any_cast<ObjectCollection>(i->second);
	
		print_object_collection (collection);

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
