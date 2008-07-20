#ifndef MOJO_FILESYSTEM_INCLUDED
#define MOJO_FILESYSTEM_INCLUDED

#include <boost/filesystem.hpp>

#include <vector>

// use a namespace alias
namespace fs = boost::filesystem;

namespace mojo {

typedef std::vector<fs::path> paths_t;

} // namespace mojo

#endif
