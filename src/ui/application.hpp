
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

	static Application& instance() { return *sm_app; }

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

	/**
	 * Create a new ProjectView if one doesn't 
	 * already exist for that project.
	 *
	 * If it does exist bring the ProjectView into into 
	 * focus.
	 */
	void open_project(const string& path_to_file);
    
private:

	static Application* sm_app;

    Application (int argc, char *argv[]);
    ~Application();

	typedef set<ProjectView*> Projects;

	Projects m_projects;

private:

	void on_projectview_signal_destroy (ProjectView*);

    /// project agnostic top level dialogs

    // about dialog
    // preferences dialog

    // edit buffer cut/paste

private:
	
	// GtkToolTips?

	/**
	 * for recieving async events from the mojo::project
	 */
	// glib::bus

private:

	struct deleter;
	friend struct deleter;

	struct deleter
	{
		void operator()(Application* app) { delete app; sm_app = 0; }
	};

};

} // namespace gmojo

#endif // GMOJO_APPLICATION_INCLUDED
