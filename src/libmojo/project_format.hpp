
#ifndef MOJO_PROJECT_FORMAT_INCLUDED
#define MOJO_PROJECT_FORMAT_INCLUDED

#include <string>

#include "project.hpp"

namespace mojo {

using std::string;

class ProjectFormat {
public:

	ProjectFormat();

	~ProjectFormat();

	// should probably take a boost::filesystem::path
	Project* load_project(const string& file_path);

	bool save_project(const Project& project,
			const string& save_location);

};

} // namespace mojo

#endif // MOJO_PROJECT_FORMAT_INCLUDED
