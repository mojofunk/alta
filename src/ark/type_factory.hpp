
#ifndef ARK_TYPE_FACTORY_INCLUDED
#define ARK_TYPE_FACTORY_INCLUDED

#include <ark/object.hpp>

namespace ark {

class TypeFactory
{
public:

	/**
	 * create an object of type type_name
	 */
	virtual Object* create (const string& type_name) = 0;

protected:

	virtual ~TypeFactory() { }

};

} // namespace ark

#endif
