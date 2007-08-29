
#ifndef MOJO_PROJECT_FORMAT_INCLUDED
#define MOJO_PROJECT_FORMAT_INCLUDED

#include <boost/noncopyable.hpp>

#include <booty/filesystem.hpp>

#include <mojo/project_ptr.hpp>

namespace mojo {

class Project;

class ProjectFormat : boost::noncopyable
{
public:

	// methods
	virtual project_ptr
		open_project (const fs::path& project_file) = 0;

	// this can't be a shared_ptr because it is called by Project
	virtual void
		save_project (const Project& project,
				const fs::path& project_file) = 0;

	// type_name ()
	//
	// extensions ()

protected:

	virtual ~ProjectFormat () { }

};

} // namespace mojo

#endif // MOJO_PROJECT_FORMAT_INCLUDED
