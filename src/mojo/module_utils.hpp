
#ifndef MOJO_MODULE_UTILS
#define MOJO_MODULE_UTILS

#include <mojo/forward.hpp>
#include <mojo/filesystem.hpp>
#include <mojo/search_path.hpp>
#include <mojo/module_set.hpp>

namespace mojo {

typedef std::vector<fs::path> paths_t;

// need a way to automatically close module
ModuleSPtr open_module (const fs::path& filepath);

bool is_module_file (const fs::path& filepath);

paths_t get_module_paths (const paths_t& directories);

ModuleSet discover_modules (const SearchPath& sp);
	
} // namespace mojo

#endif
