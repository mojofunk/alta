#ifndef MOJO_OBJECT_INCLUDED
#define MOJO_OBJECT_INCLUDED

#include <string>

#include <mojo/properties.hpp>

namespace mojo {

class Object
{
public:

	virtual void get_properties (Properties& props) const = 0;

	virtual void set_properties (const Properties& props) = 0;

protected:

	virtual ~Object() { }

};

}

#endif
