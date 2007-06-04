#ifndef MOJO_MOJO_PROJECT_FORMAT_INCLUDED
#define MOJO_MOJO_PROJECT_FORMAT_INCLUDED

#include <mojo/project_format.hpp>

namespace mojo {

class MojoProjectFormat : public ProjectFormat
{
public:

	//MojoProjectFormat () { }

	//~MojoProjectFormat () { }

	virtual Project*
		open_project (const fs::path& project_file);

	virtual void
		save_project (const Project& project,
				const fs::path& project_file);

	
};

} // namespace mojo

#endif
