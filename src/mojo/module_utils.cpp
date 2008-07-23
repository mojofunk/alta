#include <mojo/module.hpp>
#include <mojo/file_utils.hpp>

#include <mojo/module_utils.hpp>

#include <mojo/library.hpp>

#include <iostream>

using namespace std;

namespace mojo {

ModuleSPtr
open_module (const fs::path& module_path)
{
	mojo::module_func_t module_func = 0;

	mojo::LibrarySPtr lib = create_library (module_path);

	if (lib)
	{
		module_func = (mojo::module_func_t)lib->resolve ("mojo_module_factory");
	}

	if (module_func == NULL)
	{
		cerr << "factory_func == NULL" << endl;
		return mojo::ModuleSPtr();
	}

	mojo::Module* p = static_cast<mojo::Module*>(module_func());

	return mojo::ModuleSPtr(p);
}

bool
is_module_file (const fs::path& filepath)
{
	return is_library (filepath);
}

paths_t
get_module_paths (const paths_t& dirs)
{
	paths_t module_paths;

	find_matching_files (dirs, is_module_file, module_paths); 

	return module_paths;
}

ModuleSet
discover_modules (const SearchPath& sp)
{
	paths_t module_paths(get_module_paths (sp.get_directories ()));
	ModuleSet modules;
	
	std::transform (module_paths.begin(),
			module_paths.end(),
			std::insert_iterator<ModuleSet>(modules, modules.begin()),
			open_module);

	return modules;
}

} // namespace mojo
