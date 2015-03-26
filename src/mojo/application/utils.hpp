#ifndef MOJO_API_UTILS_H
#define MOJO_API_UTILS_H

#include <string>

#ifndef MOJO_APPLICATION_AMALGAMATED
#include "types.hpp"
#endif

namespace mojo {

std::string track_type_to_string(TrackType);

std::string error_to_string(Error);

} // namespace mojo

#endif // MOJO_API_UTILS_H
