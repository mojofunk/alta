
#ifndef MOJO_PROJECT_EXPORT_MODULE
#define MOJO_PROJECT_EXPORT_MODULE

#include <string>

#include "module.hpp"

namespace mojo {

/**
 * A project can be imported from another project
 * format into the native format using a ProjectImportModule
 *
 * The importer does not modify the project being imported from
 */ 
class ProjectExportModule : public Module
{
public:
	// Module Interface

	virtual std::string get_author() = 0;

	virtual std::string get_description() = 0;

	virtual std::string get_version() = 0;

public:

	/**
	 * @return The type of project format
	 */
	virtual std::string get_format_type() = 0;

	virtual std::string get_file_extension() = 0;

	// needs export directory path?
	virtual void export_project(const std::string& file_path) = 0; 
	 
};

} // namespace mojo

#endif
