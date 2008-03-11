
#ifndef GMOJO_APPLICATION_INCLUDED
#define GMOJO_APPLICATION_INCLUDED

#include <map>
#include <string>

#include <boost/shared_ptr.hpp>

#include <ui/project_ptr.hpp>
#include <ui/project_view_ptr.hpp>

namespace gmojo {

class App;

typedef boost::shared_ptr<App>    AppSPtr;
typedef boost::weak_ptr<App>      AppWPtr;

class App
{
public:

	static AppSPtr init (int argc, char *argv[]);

	/**
	 * Start the event loop and Create a new
	 * Project
	 */
	static void run();

	/**
	  must check the state of each open project,
	  if state is dirty then ask the user if they
	  want to save the project.

	  One of the options on the save dialog will be 
	  cancel in which case the application will not
	  quit, how to handle that?
	  */
	static void quit();

	/// Create a new Project.
	static void new_project();

	/**
	 * Create a new Project if one doesn't 
	 * already exist for that project.
	 *
	 * If it does exist bring the Project into into 
	 * focus.
	 */
	static void open_project(const std::string& path_to_file);

	static void close_project(Project* p);

private:

	static App* sm_app;

	App (int argc, char *argv[]);
	~App();

	typedef std::map<ProjectSPtr, ProjectViewSPtr> Projects;

	static Projects m_projects;

private:

	/// project agnostic top level dialogs

	// about dialog
	// preferences dialog

	// edit buffer cut/paste

private:
	
	// GtkToolTips?

private:

	struct deleter;
	friend struct deleter;

	struct deleter
	{
		void operator()(App* app) { delete app; sm_app = 0; }
	};

};

} // namespace gmojo

#endif // GMOJO_APPLICATION_INCLUDED
