#ifndef MOJO_MODULE_UTILS_H
#define MOJO_MODULE_UTILS_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header.hpp"
#include "mojo/core/modules/typedefs.hpp"
#include "mojo/core/filesystem/filesystem.hpp"
#include "mojo/core/filesystem/search_path.hpp"
#endif

namespace mojo {

ModuleSP open_module (const fs::path& filepath);

ModuleSPSet discover_modules (const Searchpath& sp);

template<class T>
std::set<boost::shared_ptr<T> >
get_modules_of_type (const ModuleSPSet& modules)
{
	typedef boost::shared_ptr<T> module_type;
	typedef std::set<module_type> set_type;

	set_type mods;

	for (ModuleSPSet::iterator i = modules.begin();
			i != modules.end(); ++i)
	{
		module_type p = boost::dynamic_pointer_cast<T>(*i);
		if (p) mods.insert (p);
	}
	return mods;
}

} // namespace mojo

#endif // MOJO_MODULE_UTILS_H
