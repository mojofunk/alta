
#ifndef MOJO_PROJECT_FORMAT_INCLUDED
#define MOJO_PROJECT_FORMAT_INCLUDED

#include <libmojo/object.hpp>
#include <libmojo/filesystem.hpp>

namespace mojo {

class Project;

class ProjectFormat : public Object {
public:

	virtual Project*
		open_project (const fs::path& project_file) = 0;

	virtual void
		save_project (const Project& project,
				const fs::path& project_file) = 0;

	virtual void dispose () { }

	virtual void destroy () { }

	// name ()
	//
	// extension ()
};

} // namespace mojo

#endif // MOJO_PROJECT_FORMAT_INCLUDED
