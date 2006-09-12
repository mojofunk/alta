
#ifndef NEW_PROJECT_DIALOG_HPP
#define NEW_PROJECT_DIALOG_HPP

#include <gtkmm.h>
#include <libglademm/xml.h>

#include "glade_path.hpp"
#include "glade_factory.hpp"

namespace gmojo {

struct NewProjectDialogFactory : public GladeFactory
{
    static
    Glib::RefPtr<Gnome::Glade::Xml> create();


	static
	const std::string& top_level_widget_name()
	{ return m_widget_name; };

private:

	/// top level widget name.
	/// should this just be a static const char*??
	static std::string m_widget_name;

};

class NewProjectDialog : public Gtk::Dialog
{
public:
    
    NewProjectDialog(BaseObjectType* cobject,
		     const Glib::RefPtr<Gnome::Glade::Xml>& xml);
    
    bool use_project_template() const;
    
    Glib::ustring project_template_name() const;
    
    // should we overload run()? what do we need to
    // do each time it is run?
    
    
private:

    Gtk::FileChooserButton* m_template_file_chooser_button;
    
    Gtk::Button*      m_ok_button;
    Gtk::Button*      m_cancel_button;
    
};

} // namespace gmojo

#endif // NEW_PROJECT_DIALOG_HPP
