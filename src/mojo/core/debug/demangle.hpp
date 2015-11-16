#ifndef MOJO_CORE_DEMANGLE_H
#define MOJO_CORE_DEMANGLE_H

/**
 * @param symbol a mangled symbol/name
 * @return a demangled symbol/name
 */
MOJO_API std::string demangle_symbol(const std::string& symbol);

/**
 * @param str a string containing a mangled symbol/name
 * @return a string with the mangled symbol/name replaced with a demangled
 * name
 */
MOJO_API std::string demangle(const std::string& str);

template <typename T>
std::string demangled_name(T const& obj)
{
	return demangle_symbol(typeid(obj).name());
}

#endif // MOJO_CORE_DEMANGLE_H
