
#ifndef MOJO_PROJECT_PTR_INCLUDED
#define MOJO_PROJECT_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class Project;

	typedef boost::shared_ptr<Project>    ProjectSPtr;
	typedef boost::weak_ptr<Project>      ProjectWPtr;

} // namespace mojo

#endif
