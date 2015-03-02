#include "log.hpp"

#include <iostream>

namespace mojo {

void
log (const char* log_domain, const std::string& msg)
{
	std::cerr << msg << std::endl;
}

}