
#ifndef UI_TRACK_VIEW
#define UI_TRACK_VIEW

#include <gtkmm/box.h>

namespace ui {

class Project;
class Track;

class TrackView : public Gtk::HBox
{
public: // constructors

	TrackView (Project* p);

	virtual ~TrackView ();

protected: // interface

	virtual void on_track_added (Track*) = 0;

	virtual void on_track_removed (Track*) = 0;

protected: // members

	Project* m_project;

private: // callbacks

	void on_track_added_handler (Track*);

	void on_track_removed_handler (Track*);

};

} // namespace ui

#endif
