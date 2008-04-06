
#include <gtkmm.h>

#include <iostream>

using namespace std;

void
on_quit_activate ()
{
	cout << "on_quit_activate called" << endl;
	Gtk::Main::quit ();
}

typedef Glib::RefPtr<Gtk::Builder> BuilderPtr;
typedef Glib::RefPtr<Glib::Object> ObjectPtr;
typedef Glib::RefPtr<Gtk::Action> ActionPtr;

ActionPtr
get_action (BuilderPtr& builder, const std::string& name)
{
	ObjectPtr obj = builder->get_object (name);
	return ActionPtr::cast_dynamic (obj);
}

int
main(int argc, char* argv[])
{
	Gtk::Main app (argc, argv);
	
	const std::string ui_file = "data/gmojo.ui";

	BuilderPtr builder = Gtk::Builder::create_from_file (ui_file);

	Gtk::Window * window = 0;
	builder->get_widget ("window1", window);

	ActionPtr action = get_action (builder, "quit");
	
	action->signal_activate().connect (sigc::ptr_fun (on_quit_activate));

	window->show_all ();
	app.run();

	return 0;
}
