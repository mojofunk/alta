#include <gtk/gtk.h>

#include <boost/bind.hpp>

#include <ui/app.hpp>
#include <ui/project.hpp>

namespace gmojo {

App* App::sm_app;

App::Projects App::m_projects;

AppSPtr
App::init (int argc, char *argv[])
{
	if(sm_app) throw;

	gtk_init(&argc, &argv);

	// try/catch?
	boost::shared_ptr<App> ptr(new App(argc, argv), App::deleter());

	sm_app = ptr.get();

	return ptr;
}

App::App (int argc, char *argv[])
{

}

App::~App()
{

}

void
App::run()
{
	new_project ();

	gtk_main ();
}

void
App::quit()
{
	m_projects.clear();

	gtk_main_quit ();
}

void
App::new_project()
{
	// check the return?
	m_projects.insert(ProjectSPtr(new Project));
}

void
App::open_project(const string& path_to_file)
{
    
    
}

void
App::close_project(Project* p)
{
	// ask about saving etc.

	for(Projects::iterator i = m_projects.begin();
			i != m_projects.end(); ++i)
	{
		if (p == i->get())
			m_projects.erase(i); 

		if (m_projects.empty ())
			quit();
	}
}

} // namespace gmojo
