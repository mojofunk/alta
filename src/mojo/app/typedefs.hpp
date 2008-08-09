
#ifndef MOJO_APP_TYPEDEFS
#define MOJO_APP_TYPEDEFS

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "forward.hpp"

namespace mojo {

typedef boost::shared_ptr<App>    AppSPtr;
typedef boost::weak_ptr<App>      AppWPtr;

} // namespace mojo

#endif
