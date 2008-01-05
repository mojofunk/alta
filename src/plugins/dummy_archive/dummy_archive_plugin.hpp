
#ifndef MOJO_DUMMY_ARCHIVE_PLUGIN_INCLUDED
#define MOJO_DUMMY_ARCHIVE_PLUGIN_INCLUDED

#include <mojo/plugin.hpp>

class DummyArchivePlugin : public mojo::Plugin // should be ArchivePlugin
{
public:

	virtual std::string get_author();

	virtual std::string get_description();

	virtual std::string get_version();
};

#endif
