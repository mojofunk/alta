#ifndef MOJO_OBJECT_INCLUDED
#define MOJO_OBJECT_INCLUDED

#include <string>

#include <boost/any.hpp>

namespace mojo {

class Object
{
public:

	virtual void get_property (const std::string& name,
			boost::any& value) const = 0;

	virtual void set_property (const std::string& name,
			const boost::any& value) = 0;

protected:

	virtual ~Object() { }

};

}

#endif
