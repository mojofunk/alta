
#include <ui/filesystem_paths.hpp>

#include <gleam/utils.hpp>

namespace gmojo {

fs::path
get_ui_definition_directory ()
{
	fs::path dir(gleam::getenv ("GMOJO_PATH"));

	if (!dir.empty ()) return dir / "ui";

	return fs::path();
}

} // namespace gmojo
