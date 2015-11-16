#if defined(__GLIBCXX__) // TODO move to common source includes or...
#include <cxxabi.h>
#endif

std::string demangle_symbol(const std::string& mangled_symbol)
{
#if defined(__GLIBCXX__)
	int status;

	try {
		char* realname = abi::__cxa_demangle(mangled_symbol.c_str(), 0, 0, &status);
		std::string demangled_symbol(realname);
		free(realname);
		return demangled_symbol;
	}
	catch (const std::exception&) {
	}
#endif
	return mangled_symbol;
}

std::string demangle(std::string const& str)
{
	std::string::size_type const b = str.find_first_of("(");

	if (b == std::string::npos) {
		return demangle_symbol(str);
	}

	std::string::size_type const p = str.find_last_of("+");
	if (p == std::string::npos) {
		return demangle_symbol(str);
	}

	if ((p - b) <= 1) {
		return demangle_symbol(str);
	}

	std::string const symbol = str.substr(b + 1, p - b - 1);

	return demangle_symbol(symbol);
}
