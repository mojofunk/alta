#ifndef MOJO_OBJECT
#define MOJO_OBJECT

#include "properties.hpp"

namespace mojo {

class Object
{
public:

	virtual void get_properties (Properties& props) const = 0;

	virtual void set_properties (const Properties& props) = 0;

protected:

	virtual ~Object() { }

};

} // namespace mojo

#endif
