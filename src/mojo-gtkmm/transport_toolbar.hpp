
#ifndef UI_TRANSPORT_TOOLBAR
#define UI_TRANSPORT_TOOLBAR

#include <gtkmm/box.h>

namespace ui {

class Project;

class TransportToolbar : public Gtk::HBox
{
public:
	TransportToolbar (Project* p);

	virtual ~TransportToolbar ();

protected:

	Project* m_project;
};

} // namespace ui

#endif
