
#include <mojo/export.h>

#include "xml_archive.hpp"
#include "xml_archive_module.hpp"

namespace mojo {

XMLArchiveModule::XMLArchiveModule () { }

XMLArchiveModule::~XMLArchiveModule () { }
	
Archive*
XMLArchiveModule::create_archive ()
{
	return new XMLArchive;
}

void
XMLArchiveModule::destroy_archive (Archive* ar)
{
	delete ar;
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
