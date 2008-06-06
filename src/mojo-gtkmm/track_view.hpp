
#ifndef UI_TRACK_VIEW
#define UI_TRACK_VIEW

#include <gtkmm/box.h>

namespace ui {

class Project;

class TrackView : public Gtk::HBox
{
public:
	TrackView (Project* p);

	virtual ~TrackView ();

protected:

	Project* m_project;
};

} // namespace ui

#endif
