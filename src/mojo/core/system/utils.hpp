#ifndef MOJO_CORE_SYSTEM_UTILS_H
#define MOJO_CORE_SYSTEM_UTILS_H

#ifndef MOJO_CORE_AMALGAMATED
#include <string>
#endif

namespace mojo {

/**
 * All strings are UTF-8 encoded
 */
std::string getenv(const std::string& name);
}

#endif // MOJO_CORE_SYSTEM_UTILS_H
