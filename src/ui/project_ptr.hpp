
#ifndef GMOJO_PROJECT_PTR_INCLUDED
#define GMOJO_PROJECT_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace gmojo {

	class Project;

	typedef boost::shared_ptr<Project>    ProjectSPtr;
	typedef boost::weak_ptr<Project>      ProjectWPtr;

} // namespace gmojo

#endif
