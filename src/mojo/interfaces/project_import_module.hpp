#ifndef MOJO_PROJECT_IMPORT_MODULE_H
#define MOJO_PROJECT_IMPORT_MODULE_H

#include <string>

#include "module.hpp"

namespace mojo {

class Project;

/**
 * A project can be imported from another project
 * format into the native format using a ProjectImportModule
 */ 
class ProjectImportModule : public Module
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

	// needs import directory path?
	virtual Project* import_project(const std::string& file_path) = 0; 
	 
};

}

#endif // MOJO_PROJECT_IMPORT_MODULE_H
