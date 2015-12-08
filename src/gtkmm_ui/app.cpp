namespace ui {

App* App::s_app = 0;

void App::init(int argc, char* argv[])
{
	if (s_app) throw;

	s_app = new App(argc, argv);
}

void App::cleanup()
{
	delete s_app;
}

App::App(int argc, char* argv[])
{
	mojo::Application::connect_project_added(
	    boost::bind(&App::on_project_added_handler, _1));
	mojo::Application::connect_project_removed(
	    boost::bind(&App::on_project_removed_handler, _1));
}

App::~App()
{
}

void App::run()
{
	new_project();

	Gtk::Main::run();
}

void App::quit()
{
	LOG;
	Gtk::Main::quit();
}

void App::open_project()
{
	LOG;
}

void App::new_project()
{
	LOG;
	mojo::Application::new_project();
}

void App::on_project_added_handler(mojo::Project* p)
{
	s_app->m_dispatcher.call_async(
	    sigc::bind(sigc::ptr_fun(App::on_project_added), p));
}

void App::on_project_removed_handler(mojo::Project* p)
{
	s_app->m_dispatcher.call_sync(
	    sigc::bind(sigc::ptr_fun(App::on_project_removed), p));
}

void App::on_project_added(mojo::Project* p)
{
	std::shared_ptr<ProjectObjects> po(new ProjectObjects(p));

	s_app->project_objs.insert(po);

	LOG;
}

void App::on_project_removed(mojo::Project* p)
{
	LOG;
	for (project_objects_set_t::iterator i = s_app->project_objs.begin();
	     i != s_app->project_objs.end();
	     ++i) {
		if (p == (*i)->get_project()) {
			s_app->project_objs.erase(i);
		}

		if (s_app->project_objs.empty()) {
			// this is a problem??
			quit();
		}
	}
}

void App::close_project(mojo::Project* p)
{
	// TODO ask about saving
	LOG;
	mojo::Application::close_project(p);
}

void App::save_project(mojo::Project* p)
{
	mojo::Application::save_project(p);
}

void App::add_track(mojo::Project* p)
{
	mojo::TrackOptions opt;
	// bring up add audio track dialog
	mojo::Application::add_track(p, opt);
}

void App::open_project_setup_dialog(mojo::Project* proj)
{
	LOG;
	ProjectSetupDialog dialog(proj);

	dialog.run();
}

void App::open_preferences_dialog()
{
	PreferencesDialog dialog;
	LOG;

	dialog.run();
}

void App::open_import_dialog()
{
	ImportDialog dialog;
	LOG;

	dialog.run();
}

Dispatcher& App::get_dispatcher()
{
	return s_app->m_dispatcher;
}

} // namespace ui
