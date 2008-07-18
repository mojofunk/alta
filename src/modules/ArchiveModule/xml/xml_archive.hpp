
#ifndef MOJO_XML_ARCHIVE
#define MOJO_XML_ARCHIVE

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

	virtual void write (const std::string& file_path, const Properties& props);
	
	virtual void read (const std::string& file_path, Properties& props);

};

} // namespace mojo

#endif
