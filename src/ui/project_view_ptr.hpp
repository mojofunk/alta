
#ifndef GMOJO_PROJECT_VIEW_PTR
#define GMOJO_PROJECT_VIEW_PTR

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace gmojo {

	class ProjectView;

	typedef boost::shared_ptr<ProjectView>    ProjectViewSPtr;
	typedef boost::weak_ptr<ProjectView>      ProjectViewWPtr;

} // namespace gmojo

#endif

