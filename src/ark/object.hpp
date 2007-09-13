
#ifndef ARK_OBJECT_INCLUDED
#define ARK_OBJECT_INCLUDED

#include <ark/property.hpp>

namespace ark {

/**
 * A Class that is capable of being stored in an archive.
 */
class Object
{
public:

	virtual void get_properties (Properties& properties) const = 0;

	virtual void set_properties (const Properties& properties) = 0;

	// notify signal ??

protected:

	virtual ~Object() { }

};

} // namespace ark

#endif
