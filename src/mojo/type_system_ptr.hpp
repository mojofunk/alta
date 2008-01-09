
#ifndef MOJO_TYPE_SYSTEM_PTR_INCLUDED
#define MOJO_TYPE_SYSTEM_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class TypeSystem;

	typedef boost::shared_ptr<TypeSystem>    TypeSystemSPtr;
	typedef boost::weak_ptr<TypeSystem>      TypeSystemWPtr;

} // namespace mojo

#endif
