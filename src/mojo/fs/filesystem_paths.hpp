
#ifndef MOJO_FILESYSTEM_PATHS
#define MOJO_FILESYSTEM_PATHS

#include <mojo/core/filesystem.hpp>

#include <mojo/utils/search_path.hpp>

namespace mojo {

	fs::path user_config_directory();

	SearchPath mojo_search_path();

	SearchPath system_config_search_path();

	SearchPath system_data_search_path();

	SearchPath module_search_path();

} // namespace mojo

#endif
