
#ifndef UI_TRANSPORT_TOOLBAR
#define UI_TRANSPORT_TOOLBAR

#include <gtkmm/box.h>

#include <mojo/mojo.hpp>

namespace ui {

class Project;

class TransportToolbar : public Gtk::HBox
{
public:
	TransportToolbar (mojo::Project* p);

	virtual ~TransportToolbar ();

protected:

	mojo::Project* m_project;
};

} // namespace ui

#endif
