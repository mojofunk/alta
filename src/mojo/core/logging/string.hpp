#ifndef MOJO_LOGGING_STRING_H
#define MOJO_LOGGING_STRING_H

namespace logging {

using String = std::basic_string<char, std::char_traits<char>, Allocator<char>>;

} // namespace logging

#endif // MOJO_LOGGING_STRING_H
