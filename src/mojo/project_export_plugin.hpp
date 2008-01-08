
#ifndef MOJO_PROJECT_EXPORT_PLUGIN_INCLUDED
#define MOJO_PROJECT_EXPORT_PLUGIN_INCLUDED

#include <string>

#include <mojo/plugin.hpp>
#include <mojo/project_ptr.hpp>

namespace mojo {

using std::string;

/**
 * A project can be imported from another project
 * format into the native format using a ProjectImportPlugin
 *
 * The importer does not modify the project being imported from
 */ 
class ProjectExportPlugin : public Plugin
{
public:
	// Plugin Interface

	virtual std::string get_author() = 0;

	virtual std::string get_description() = 0;

	virtual std::string get_version() = 0;

public:

	/**
	 * @return The type of project format
	 */
	virtual string get_format_type() = 0;

	virtual string get_file_extension() = 0;

	// needs export directory path?
	virtual void export_project(const string& file_path) = 0; 
	 
};

}

#endif
