#ifndef MOJO_CORE_LOG_FORMAT_H
#define MOJO_CORE_LOG_FORMAT_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#include "mojo/core/logging/log_allocator.hpp"
#include "mojo/core/logging/log_string.hpp"
#endif

namespace mojo {

MOJO_API
LogString log_format(LogAllocator<char>& alloc,
                     fmt::StringRef format_str,
                     fmt::ArgList args);

FMT_VARIADIC(LogString, log_format, LogAllocator<char>, fmt::StringRef)

} // namespace mojo

#endif // MOJO_CORE_LOG_FORMAT_H
