#ifndef MOJO_FILESYSTEM_H
#define MOJO_FILESYSTEM_H

#include <boost/filesystem.hpp>

#include <vector>

// use a namespace alias
namespace fs = boost::filesystem;

namespace mojo {

typedef std::vector<fs::path> paths_t;

} // namespace mojo

#endif // MOJO_FILESYSTEM_H
