
#ifndef MOJO_API_PROPERTY
#define MOJO_API_PROPERTY

// TODO copy boost any so as not to depend on boost
#include <boost/any.hpp>

namespace mojo {

struct Property
{
	std::string name;
	boost::any value; 

};

} // namespace mojo

#endif
