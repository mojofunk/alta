
#ifndef GMOJO_PROJECT_PTR
#define GMOJO_PROJECT_PTR

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace gmojo {

	class Project;

	typedef boost::shared_ptr<Project>    ProjectSPtr;
	typedef boost::weak_ptr<Project>      ProjectWPtr;

} // namespace gmojo

#endif
