
#ifndef MOJO_FILE_UTILS_INCLUDED
#define MOJO_FILE_UTILS_INCLUDED

#include <booty/filesystem.hpp>

namespace mojo {

/**
 * Given a full path to a file that may or may not exist,
 * return a unique non-existing file path.
 */
const fs::path get_non_existent_file_path (const fs::path& file_path);

} // namespace mojo

#endif // MOJO_FILE_UTILS_INCLUDED
