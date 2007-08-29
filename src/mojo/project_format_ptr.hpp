
#ifndef MOJO_PROJECT_FORMAT_PTR_INCLUDED
#define MOJO_PROJECT_FORMAT_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class ProjectFormat;

	typedef boost::shared_ptr<ProjectFormat>    project_format_ptr;
	typedef boost::weak_ptr<ProjectFormat>      project_format_wptr;

} // namespace mojo

#endif
