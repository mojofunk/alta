
#ifndef MOJO_PROJECT_IMPORT_PLUGIN_INCLUDED
#define MOJO_PROJECT_IMPORT_PLUGIN_INCLUDED

#include <string>

#include <mojo/plugin.hpp>
#include <mojo/project_ptr.hpp>

namespace mojo {

using std::string;

/**
 * A project can be imported from another project
 * format into the native format using a ProjectImportPlugin
 */ 
class ProjectImportPlugin : public Plugin
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

	// needs import directory path?
	virtual ProjectSPtr import_project(const string& file_path) = 0; 
	 
};

}

#endif
