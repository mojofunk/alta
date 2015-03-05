#ifndef MOJO_CORE_FILESYSTEM_H
#define MOJO_CORE_FILESYSTEM_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header.hpp"
#endif

// use a namespace alias
namespace fs = boost::filesystem;

namespace mojo {

typedef std::vector<fs::path> paths_t;

} // namespace mojo

#endif // MOJO_CORE_FILESYSTEM_H
