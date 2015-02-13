
#include "filesystem_paths.hpp"

#include <gleam/filesystem_paths.hpp>
#include <gleam/utils.hpp>

#include "mojo/fs/file_utils.hpp"

namespace ui {

using namespace mojo;

Searchpath
gmojo_search_path()
{
	return Searchpath(gleam::getenv ("GMOJO_PATH"));
}

Searchpath
system_config_search_path()
{
	Searchpath sp(gleam::get_system_config_directories ());
	sp / "gmojo";
	return sp;
}

Searchpath
system_data_search_path()
{
	Searchpath sp(gleam::get_system_data_directories ());
	sp / "gmojo";
	return sp;
}

std::string
get_ui_filepath (const std::string& filename)
{
	Searchpath sp(gmojo_search_path() + system_data_search_path ());

	fs::path filepath;

	find_matching_file (sp.get_paths().front(), filename, filepath);

	return filepath.string();
}

} // namespace ui
