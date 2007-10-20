
#ifndef ARK_OBJECT_INCLUDED
#define ARK_OBJECT_INCLUDED

#include <string>
#include <boost/any.hpp>

namespace ark {

/**
 * A Class that is capable of being stored in an archive.
 */
class Object
{
public:

	virtual void get_property (const std::string& name, boost::any& value) const = 0;

	virtual void set_property (const std::string& name, const boost::any& value) = 0;

protected:

	virtual ~Object() { }

};

} // namespace ark

#endif
