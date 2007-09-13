
#include <ark/export.h>

#include "archive.hpp"

namespace ark {

ArchiveWriter*
DummyDescriptor::create_writer()
{
	return new DummyArchive;
}

ArchiveReader*
DummyDescriptor::create_reader()
{
	return new DummyArchive;
}

ModuleInfo
DummyDescriptor::get_info()
{

	return ModuleInfo("blah", "bloh", ArchiveFormat("", ""));
}

void
DummyArchive::read (const string& file_path, const TypeFactory& type_factory)
{

}

Object*
DummyArchive::get_object (const string& name)
{

}


void
DummyArchive::add_object (const string& name, const Object&)
{

}

void
DummyArchive::write (const string& file_path, const TypeNameRegistry& registry)
{

}

ARK_CAPI void * ark_descriptor ()
{
	return new DummyDescriptor;
}


} // namespace ark
