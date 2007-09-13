
#ifndef ARK_MODULE_INFO_INCLUDED
#define ARK_MODULE_INFO_INCLUDED

#include <string>

#include <ark/archive_format.hpp>

namespace ark {

using std::string;

/**
 * The ModuleInfo class holds information about a the
 * module. A module is loaded, the ModuleInfo is
 * extracted and then it is unloaded.
 */
class ModuleInfo
{
public:

	ModuleInfo(const string& path,
			const string& name,
			const ArchiveFormat& format)

		:
			path(path),
			name(name),
			format(format)
	{ }

	const string               path;
	const string               name;

	const ArchiveFormat        format;

};

} // namespace ark

#endif
