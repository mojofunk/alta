#include <mojo/module.hpp>

#include <mojo/utils/file_utils.hpp>
#include <mojo/utils/library.hpp>

#include "module_utils.hpp"

namespace mojo {

ModuleSPtr
open_module (const fs::path& module_path)
{
	Module::factory_func_t factory = 0;

	LibrarySPtr lib = create_library (module_path);

	if (lib)
	{
		factory = (Module::factory_func_t)lib->resolve ("mojo_module_factory");
	}

	if (factory == NULL)
	{
		return mojo::ModuleSPtr();
	}

	mojo::Module* p = static_cast<mojo::Module*>(factory());

	return mojo::ModuleSPtr(p);
}

ModuleSet
discover_modules (const SearchPath& sp)
{
	paths_t module_paths;
	
	find_matching_files (sp.get_paths (), is_library, module_paths);

	ModuleSet modules;
	
	std::transform (module_paths.begin(),
			module_paths.end(),
			std::insert_iterator<ModuleSet>(modules, modules.begin()),
			open_module);

	return modules;
}

} // namespace mojo
