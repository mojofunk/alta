
#ifndef MOJO_OBJECT_PTR_INCLUDED
#define MOJO_OBJECT_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class Object;

	typedef boost::shared_ptr<Object>    ObjectSPtr;
	typedef boost::weak_ptr<Object>      ObjectWPtr;

} // namespace mojo

#endif
