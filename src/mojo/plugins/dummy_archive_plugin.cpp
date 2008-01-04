#include <mojo/export.h>

#include "dummy_archive_plugin.hpp"

std::string
DummyArchivePlugin::get_author()
{
	return "Tim Mayberry";
}

std::string
DummyArchivePlugin::get_description()
{
	return "This is a Dummy Plugin for test purposes";
}

std::string
DummyArchivePlugin::get_version()
{
	return "0.0.1";
}

MOJO_CAPI void * mojo_plugin_factory(void)
{
	return new DummyArchivePlugin;
}
