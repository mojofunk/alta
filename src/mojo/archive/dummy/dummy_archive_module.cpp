
#include "dummy_archive.hpp"
#include "dummy_archive_module.hpp"

namespace mojo {

DummyArchiveModule::DummyArchiveModule() {}

DummyArchiveModule::~DummyArchiveModule() {}

ArchiveSP DummyArchiveModule::create_archive()
{
	return ArchiveSP(new DummyArchive);
}

std::string DummyArchiveModule::get_author() { return "Tim Mayberry"; }

std::string DummyArchiveModule::get_description()
{
	return "DummyArchive module";
}

std::string DummyArchiveModule::get_version() { return "0.0.1"; }

MOJO_CAPI void* mojo_module_factory(void) { return new DummyArchiveModule; }

} // namespace mojo
