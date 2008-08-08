
#ifndef MOJO_TYPESYSTEM_TYPEDEFS
#define MOJO_TYPESYSTEM_TYPEDEFS

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <mojo/typesystem/forward.hpp>

namespace mojo {

typedef boost::shared_ptr<TypeFactory>    TypeFactorySPtr;
typedef boost::weak_ptr<TypeFactory>      TypeFactoryWPtr; 

typedef boost::shared_ptr<TypeSystem>    TypeSystemSPtr;
typedef boost::weak_ptr<TypeSystem>      TypeSystemWPtr;

} // namespace mojo




#endif
