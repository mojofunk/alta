
#ifndef UI_FILESYSTEM_PATHS
#define UI_FILESYSTEM_PATHS

// this needs to be private or in another lib
#include <mojo/fs/search_path.hpp>

namespace ui {

	mojo::SearchPath gmojo_search_path();

	mojo::SearchPath system_config_search_path();

	mojo::SearchPath system_data_search_path();

	std::string get_ui_filepath (const std::string& filename);

} // namespace ui

#endif
