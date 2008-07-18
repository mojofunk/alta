
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

template<class T>
std::set<boost::shared_ptr<T> >
get_modules_of_type (const ModuleSet& modules)
{
	typedef boost::shared_ptr<T> module_type;
	typedef std::set<module_type> set_type;

	set_type mods;

	for (ModuleSet::iterator i = modules.begin();
			i != modules.end(); ++i)
	{
		module_type p = boost::dynamic_pointer_cast<T>(*i);
		if (p) mods.insert (p);
	}
	return mods;
}
	
} // namespace mojo

#endif
