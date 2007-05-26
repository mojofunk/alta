
#ifndef GMOJO_EDIT_WINDOW_MENU_BAR_INCLUDED
#define GMOJO_EDIT_WINDOW_MENU_BAR_INCLUDED

#include <gtk/gtk.h>

#include <boost/noncopyable.hpp>

#include <ui/gtk_ui_manager.hpp>

namespace gmojo {

class EditWindowMenuBar : boost::noncopyable
{
public:

	EditWindowMenuBar(boost::intrusive_ptr<GtkUIManager> ui_manager);

	~EditWindowMenuBar();

	GtkWidget* widget() { return m_menu_bar; }

private:

	GtkWidget* m_menu_bar;

};

} // namespace gmojo

#endif
