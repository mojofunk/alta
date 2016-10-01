#ifndef MOJO_LOGGING_FORMAT_H
#define MOJO_LOGGING_FORMAT_H

namespace logging {

MOJO_API
String
format(Allocator<char> alloc, fmt::CStringRef format_str, fmt::ArgList args);

FMT_VARIADIC(String, format, Allocator<char>, fmt::CStringRef)
}

#endif // MOJO_LOGGING_FORMAT_H
