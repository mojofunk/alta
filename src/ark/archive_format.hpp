
#ifndef ARK_ARCHIVE_FORMAT_INCLUDED
#define ARK_ARCHIVE_FORMAT_INCLUDED

#include <string>

namespace ark {

using std::string;

class ArchiveFormat
{
public:

	ArchiveFormat(const string& name,
			const string& extension)
		:
			name(name),
			extension(extension)
	{ }

	const string name;
	const string extension;

};

} // namespace ark

#endif
