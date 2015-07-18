#ifndef MOJO_AMALGAMATED
#include "dummy_archive.hpp"

#include <iostream>
#include <fstream>

#include <mojo/core/object/object.hpp>
#include <mojo/core/typesystem/type_system.hpp>
#include <mojo/core/string/convert.hpp>

#endif

namespace mojo {

using namespace std;

void DummyArchive::read(const fs::path& file_path, Properties& props)
{
}

void DummyArchive::write_object(std::ostream& os, const ObjectSP& obj)
{
	const string type_name = types::get_type_name(typeid(*obj));

	os << " Type: " << type_name << " ";

	Properties props;

	obj->get_properties(props);

	for (Properties::const_iterator i = props.begin(); i != props.end();) {
		write_property(os, *i);

		++i;

		if (i != props.end()) {
			os << ", ";
		}
	}

	os << std::endl;
}

void DummyArchive::write_object_collection(std::ostream& os,
                                           const ObjectCollection& col)
{
	for (ObjectCollection::const_iterator i = col.begin(); i != col.end(); ++i) {
		write_object(os, *i);
	}
}

void DummyArchive::write_property(std::ostream& os, const Property& prop)
{
	string type_name = types::get_type_name(prop.value.type());

	os << "Name: " << prop.get_name_string() << " Type: " << type_name
	   << " Value: ";

	if (prop.value.type() == typeid(ObjectCollection)) {
		write_object_collection(os, boost::any_cast<ObjectCollection>(prop.value));
	} else if (prop.value.type() == typeid(std::string)) {
		os << boost::any_cast<std::string>(prop.value);
	} else if (prop.value.type() == typeid(ObjectSP)) {
		write_object(os, boost::any_cast<ObjectSP>(prop.value));
	} else if (prop.value.type() == typeid(int64_t)) {
		string tmp;
		to_string(boost::any_cast<int64_t>(prop.value), tmp);
		os << tmp;
	} else if (prop.value.type() == typeid(int32_t)) {
		string tmp;
		to_string(boost::any_cast<int32_t>(prop.value), tmp);
		os << tmp;
	} else if (prop.value.type() == typeid(float)) {
		string tmp;
		to_string(boost::any_cast<float>(prop.value), tmp);
		os << tmp;
	}
}

void DummyArchive::write(const fs::path& file_path, const Properties& props)
{
	std::ofstream output_file(file_path.string().c_str());

	for (Properties::const_iterator i = props.begin(); i != props.end(); ++i) {
		write_property(output_file, *i);
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
