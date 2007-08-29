
#ifndef MOJO_PROJECT_PTR_FWD_INCLUDED
#define MOJO_PROJECT_PTR_FWD_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class Project;

	typedef boost::shared_ptr<Project>    project_ptr;
	typedef boost::weak_ptr<Project>      project_wptr;

} // namespace mojo

#endif
