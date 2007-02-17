
#ifndef GMOJO_PROJECT_VIEW_INCLUDED
#define GMOJO_PROJECT_VIEW_INCLUDED

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <libmojo/project.hpp>

namespace gmojo {

class TrackView;

/**
   The project view is intended to be the central
   class through which all the different Views of
   the project are created and accessed.
*/
class ProjectView : boost::noncopyable
{
public:
	

	void run();

//   mojo::Project& project() { return *m_project; }

	static boost::shared_ptr<ProjectView> create (mojo::project project);


private:

	struct deleter;
	friend struct deleter;

	struct deleter
	{
		void operator()(ProjectView* p) { delete p; }
	};

    ProjectView(mojo::project project);

    ~ProjectView();

	mojo::project m_project;	
    
   // TrackView* m_trackview;
    
    // TransportControl m_transport_control;
    
};

} // namespace gmojo

#endif // GMOJO_PROJECT_VIEW_INCLUDED
