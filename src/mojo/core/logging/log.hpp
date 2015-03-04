#ifndef MOJO_CORE_LOG_H
#define MOJO_CORE_LOG_H

#include <string>

#include "mojo/core/visibility.hpp"

namespace mojo {

void log (const char* log_domain, const std::string& msg);

}

#endif // MOJO_CORE_LOG_H
