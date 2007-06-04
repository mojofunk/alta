
#ifndef MOJO_PROJECT_FORMAT_INCLUDED
#define MOJO_PROJECT_FORMAT_INCLUDED

#include <boost/shared_ptr.hpp>

#include <booty/filesystem.hpp>

namespace mojo {

class Project;

class ProjectFormat {
public:

	typedef boost::shared_ptr<ProjectFormat> ptr;

	virtual ~ProjectFormat () { }

public:

	virtual Project*
		open_project (const fs::path& project_file) = 0;

	virtual void
		save_project (const Project& project,
				const fs::path& project_file) = 0;

	// type_name ()
	//
	// extensions ()
};

} // namespace mojo

#endif // MOJO_PROJECT_FORMAT_INCLUDED
