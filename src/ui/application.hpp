
#ifndef GMOJO_APPLICATION_INCLUDED
#define GMOJO_APPLICATION_INCLUDED

#include <set>
#include <string>

#include <boost/shared_ptr.hpp>

namespace gmojo {

using std::set;
using std::string;

class ProjectView;

class Application
{
public:

	static boost::shared_ptr<Application> create (int argc, char *argv[]);

	Application& instance() { return *sm_app; }

	/**
	 * Start the event loop and Create a new
	 * ProjectView
	 */
    void run();
    
    /**
      must check the state of each open project,
      if state is dirty then ask the user if they
      want to save the project.

	  One of the options on the save dialog will be 
	  cancel in which case the application will not
	  quit, how to handle that?
    */
    void quit();
    
    /// Create a new ProjectView.
    void new_project();
    
private:

	static Application* sm_app;

	struct deleter;
	friend struct deleter;

	struct deleter
	{
		void operator()(Application* app) { delete app; sm_app = 0; }
	};

    Application (int argc, char *argv[]);
    ~Application();

	typedef set<boost::shared_ptr<ProjectView> > Projects;

	Projects m_projects;

	/**
	 * Create a new ProjectView if one doesn't 
	 * already exist for that project.
	 *
	 * If it does exist bring the ProjectView into into focus.
	 */
	void open_project(const string& path_to_file);
        
    /// project agnostic top level dialogs

    // about dialog
    // preferences dialog
    // tool

    // edit buffer cut/paste

};

} // namespace gmojo

#endif // GMOJO_APPLICATION_INCLUDED
