
#ifndef MOJO_TYPE_FACTORY_INCLUDED
#define MOJO_TYPE_FACTORY_INCLUDED

#include <string>
#include <typeinfo>

#include <boost/any.hpp>

namespace mojo {

class TypeFactory
{
public:

	virtual std::string type_name() const = 0;

	/// create always returns a pointer to a newly
	/// allocated type. 
	virtual boost::any create() const = 0;

	virtual const std::type_info& type_info() const = 0;

protected:

	virtual ~TypeFactory() { }
};

} // namespace mojo

#endif
