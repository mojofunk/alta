
#ifndef MOJO_TYPE_FACTORY_PTR_INCLUDED
#define MOJO_TYPE_FACTORY_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class TypeFactory;

	typedef boost::shared_ptr<TypeFactory>    TypeFactorySPtr;
	typedef boost::weak_ptr<TypeFactory>      TypeFactoryWPtr;

} // namespace mojo

#endif
