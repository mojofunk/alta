#ifndef MOJO_CORE_LOGGING_H
#define MOJO_CORE_LOGGING_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#endif

namespace mojo {

MOJO_API void* log_malloc(std::size_t size);

MOJO_API void log_free(void* ptr);

MOJO_API void log_initialize();

MOJO_API void log_deinitialize();

} // namespace mojo

#endif // MOJO_CORE_LOGGING_H
