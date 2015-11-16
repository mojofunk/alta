#ifndef MOJO_MODULE_UTILS_H
#define MOJO_MODULE_UTILS_H

namespace mojo {

ModuleSP open_module(const fs::path& filepath);

ModuleSPSet discover_modules(const Searchpath& sp);

template <class T>
std::set<std::shared_ptr<T>> get_modules_of_type(const ModuleSPSet& modules)
{
	typedef std::shared_ptr<T> module_type;
	typedef std::set<module_type> set_type;

	set_type mods;

	for (ModuleSPSet::iterator i = modules.begin(); i != modules.end(); ++i) {
		module_type p = std::dynamic_pointer_cast<T>(*i);
		if (p) mods.insert(p);
	}
	return mods;
}

} // namespace mojo

#endif // MOJO_MODULE_UTILS_H
