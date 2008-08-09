
#ifndef MOJO_UTILS_TYPEDEFS
#define MOJO_UTILS_TYPEDEFS

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "forward.hpp"

namespace mojo {

typedef boost::shared_ptr<Library>    LibrarySPtr;
typedef boost::weak_ptr<Library>      LibraryWPtr;

} // namespace mojo

#endif
