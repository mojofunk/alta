
#ifndef MOJO_TYPE_INCLUDED
#define MOJO_TYPE_INCLUDED

#include <string>
#include <typeinfo>

#include <boost/any.hpp>

namespace mojo {

class Type
{
public:

	virtual std::string type_name() const = 0;

	virtual boost::any create() const = 0;

	virtual const std::type_info& type_info() const = 0;

protected:

	virtual ~Type() { }
};

} // namespace mojo

#endif
