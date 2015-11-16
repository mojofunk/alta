#ifndef MOJO_CORE_LOG_FORMAT_H
#define MOJO_CORE_LOG_FORMAT_H

MOJO_API
LogString log_format(LogAllocator<char>& alloc,
                     fmt::StringRef format_str,
                     fmt::ArgList args);

FMT_VARIADIC(LogString, log_format, LogAllocator<char>, fmt::StringRef)

#endif // MOJO_CORE_LOG_FORMAT_H
