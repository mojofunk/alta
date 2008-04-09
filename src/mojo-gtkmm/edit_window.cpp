
#include "project.hpp"
#include "app.hpp"
#include "edit_window.hpp"

#include "types.hpp"

namespace ui {

ActionPtr
get_action (BuilderPtr& builder, const std::string& name)
{
	ObjectPtr obj = builder->get_object (name);
	return ActionPtr::cast_dynamic (obj);
}

void
connect_action (BuilderPtr& builder, const std::string& name, 
	   	const sigc::slot<void>& slot)
{
	ActionPtr action = get_action (builder, name);

	if (action)
		action->signal_activate().connect (slot);

}

EditWindow::EditWindow (Project* proj)
	: m_project(proj)
{
	const std::string ui_file = "data/gmojo.ui";

	BuilderPtr builder = Gtk::Builder::create_from_file (ui_file);

	builder->get_widget ("editwindow", m_window);

	connect_action (builder, "new-project-menuitem", sigc::ptr_fun (App::new_project));
	connect_action (builder, "open-project-menuitem", sigc::ptr_fun (App::open_project));
	connect_action (builder, "save-project-menuitem", sigc::mem_fun (m_project, &Project::save));
	connect_action (builder, "close-project-menuitem", sigc::bind ( sigc::ptr_fun (&App::close_project), m_project));
	connect_action (builder, "quit-menuitem", sigc::ptr_fun (App::quit));

	m_window->signal_delete_event().connect (sigc::mem_fun (this, &EditWindow::on_delete_event));
	m_window->show_all ();
}

EditWindow::~EditWindow ()
{
	delete m_window;
}

bool
EditWindow::on_delete_event (GdkEventAny*)
{
	App::close_project (m_project);
	return true;
}

} // namespace ui
