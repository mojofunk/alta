#ifndef MOJO_CORE_LOG_STRING_H
#define MOJO_CORE_LOG_STRING_H

namespace mojo {

typedef std::basic_string<char, std::char_traits<char>, LogAllocator<char>>
    LogString;

} // namespace mojo

#endif // MOJO_CORE_LOG_STRING_H
