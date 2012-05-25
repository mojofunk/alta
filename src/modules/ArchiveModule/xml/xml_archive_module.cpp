
#include "xml_archive.hpp"
#include "xml_archive_module.hpp"

#include "mojo/core/export.h"

namespace mojo {

XMLArchiveModule::XMLArchiveModule () { }

XMLArchiveModule::~XMLArchiveModule () { }
	
ArchiveSP
XMLArchiveModule::create_archive ()
{
	return ArchiveSP(new XMLArchive);
}

std::string
XMLArchiveModule::get_author()
{
	return "Tim Mayberry";
}

std::string
XMLArchiveModule::get_description()
{
	return "XMLArchive module";
}

std::string
XMLArchiveModule::get_version()
{
	return "0.0.1";
}

MOJO_CAPI void * mojo_module_factory(void)
{
	return new XMLArchiveModule;
}

} // namespace mojo
