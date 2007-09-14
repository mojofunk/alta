
#ifndef ARK_DESCRIPTOR_INCLUDED
#define ARK_DESCRIPTOR_INCLUDED

#include <ark/module_info.hpp>
#include <ark/archive_reader.hpp>
#include <ark/archive_writer.hpp>

namespace ark {

class Descriptor
{
public:

	virtual ~Descriptor() { }

public:

	virtual ArchiveWriter* create_writer() = 0;

	virtual ArchiveReader* create_reader() = 0;

	virtual ModuleInfo get_info() = 0;


};

} // namespace ark

#endif
