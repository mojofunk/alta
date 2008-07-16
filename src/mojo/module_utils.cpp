#include <gmodule.h>

#include <map>

#include <mojo/module.hpp>
#include <mojo/file_utils.hpp>

#include <mojo/module_utils.hpp>

#include <iostream>

using namespace std;

typedef std::map<mojo::Module*, GModule*> ModuleMap;

namespace {

ModuleMap* module_map = 0;

void
_close_module (mojo::Module* module)
{
	ModuleMap::iterator i = module_map->find (module);
	GModule* m = i->second;

	if (i == module_map->end()) return;

	// The module was allocated in a dynamically opened module
	// so the memory has to be deleted while the module is open.
	// and possibly from within the dll on windows?
	module_map->erase(i);
	delete module;

	if (g_module_close (m) != TRUE)
	{
		cerr << "Unable to close module" << endl;
	}
}

mojo::ModuleSPtr
_open_module (const std::string& module_path)
{
	GModule* module = NULL;
	mojo::module_func_t module_func = 0;

	module = g_module_open(module_path.c_str(), G_MODULE_BIND_LAZY);

	if (module == NULL)
	{
		cerr << "module == NULL:" << g_module_error() << endl;
		return mojo::ModuleSPtr();
	} 

	if (g_module_symbol(module, "mojo_module_factory",
				(gpointer*)&module_func) == FALSE)
	{
		cerr << "Could not resolve symbol while opening module" << endl;
		return mojo::ModuleSPtr();
	}

	if (module_func == NULL)
	{
		cerr << "factory_func == NULL" << endl;
		return mojo::ModuleSPtr();
	}

	mojo::Module* p = static_cast<mojo::Module*>(module_func());

	mojo::ModuleSPtr mod(p, _close_module);

	// XXX check
	module_map->insert (std::make_pair(p, module));

	return mod;
}

} // unnamed namespace

namespace mojo {

ModuleSPtr
open_module (const fs::path& module_path)
{
	if (module_map == 0)
	{
		module_map = new ModuleMap;
	}

	return _open_module(module_path.string());
}

bool
is_module_file (const fs::path& filepath)
{
	return (fs::extension (filepath) == "." G_MODULE_SUFFIX);
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
