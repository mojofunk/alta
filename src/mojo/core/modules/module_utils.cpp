#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"
#include "mojo/core/modules/module_utils.hpp"
#include "mojo/core/modules/module.hpp"
#include "mojo/core/modules/library.hpp"
#include "mojo/core/filesystem/file_utils.hpp"
#endif

namespace mojo {

ModuleSP open_module(const fs::path& module_path)
{
	Module::factory_func_t factory = 0;

	LibrarySP lib = create_library(module_path);

	if (lib) {
		factory = (Module::factory_func_t)lib->resolve("mojo_module_factory");
	}

	if (factory == NULL) {
		return mojo::ModuleSP();
	}

	mojo::Module* p = static_cast<mojo::Module*>(factory());

	return mojo::ModuleSP(p);
}

ModuleSPSet discover_modules(const Searchpath& sp)
{
	paths_t module_paths;

	find_matching_files(sp.get_paths(), is_library, module_paths);

	ModuleSPSet modules;

	for (auto const& path : module_paths) {
		ModuleSP mod = open_module(path);
		if (mod) modules.insert(mod);
	}

	return modules;
}

} // namespace mojo
