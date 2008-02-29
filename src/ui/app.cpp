#include <boost/bind.hpp>

#include <mojo/project.hpp>
#include <mojo/project_ptr.hpp>

#include <ui/app.hpp>
#include <ui/project_view.hpp>

namespace gmojo {

App* App::sm_app;

boost::shared_ptr<App>
App::create (int argc, char *argv[])
{
	if(sm_app) throw;

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
	mojo::ProjectSPtr new_project(new mojo::Project());

	ProjectView::ptr pview(new ProjectView (new_project));

#if 0
	// a reference to the project is not held by this class
	// so if the project is destroyed rely on the projectview's
	// destroy signal
	pview->on_destroy (
		 boost::bind (
			 &App::on_projectview_signal_destroy, this,
			 ProjectView::weak_ptr(pview)
			 )
		);

#endif

	// check the return?
	m_projects.insert(pview);
}

void
App::on_projectview_signal_destroy (ProjectView::weak_ptr projectview)
{
	ProjectView::ptr pview(projectview.lock ());
	
	// check
	m_projects.erase(pview);

	if(m_projects.empty ())
	{
		quit();
	}
}

void
App::open_project(const string& path_to_file)
{
    
    
}

void
App::close_project(mojo::Project* p)
{
	// ask about saving etc.

	for(Projects::iterator i = App::instance().m_projects.begin();
			i != App::instance().m_projects.end(); ++i)
	{
		if (p == (*i)->get_project().get())
		{
			App::instance().m_projects.erase(i);
		}

		if (App::instance().m_projects.empty ())
		{
			App::instance().quit();
		}
	}
}

} // namespace gmojo
