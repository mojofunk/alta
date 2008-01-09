
#ifndef MOJO_TYPE_PTR_INCLUDED
#define MOJO_TYPE_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class Type;

	typedef boost::shared_ptr<Type>    TypeSPtr;
	typedef boost::weak_ptr<Type>      TypeWPtr;

} // namespace mojo

#endif
