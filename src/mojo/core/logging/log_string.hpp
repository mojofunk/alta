#ifndef MOJO_CORE_LOG_STRING_H
#define MOJO_CORE_LOG_STRING_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#include "mojo/core/logging/log_allocator.hpp"
#endif

namespace mojo {

typedef std::basic_string<char, std::char_traits<char>, LogAllocator<char>>
    LogString;

} // namespace mojo

#endif // MOJO_CORE_LOG_STRING_H
