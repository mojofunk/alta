
#ifndef MOJO_XML_ARCHIVE_INCLUDED
#define MOJO_XML_ARCHIVE_INCLUDED

#include <mojo/archive.hpp>

namespace mojo {

/**

  Top level elements must have a name attribute

  XML element names are the type names registered in the TypeSystem, properties
  could use the property name as the element name but that would be inconsitant
  for collections where each type instance can only be identified by an id where
  the id is generated from the address of the object.

  Object properties are child elements

  Each object has a unique id number

  A collection contains references to types defined elsewhere 

  Should an Object be defined where it is first referenced, or should references
  by inserted and the object defined elsewhere.

  Archives are only expected to know about the Object class so all references
  must be stored as objectref types and then referenced by id 
 */
class XMLArchive : public Archive
{
public:

	virtual void set_property (const std::string& name,
			const boost::any& value);

	virtual void write (const std::string& file_path);
	
	virtual void read (const std::string& file_path);

	virtual void get_property (const std::string& name,
			boost::any& value);
};

} // namespace mojo

#endif
