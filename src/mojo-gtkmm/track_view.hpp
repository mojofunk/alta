
#ifndef UI_TRACK_VIEW
#define UI_TRACK_VIEW

#include <gtkmm/paned.h>

namespace ui {

class Project;
class Track;
class TrackViewData;

class TrackView : public Gtk::HPaned
{
public: // constructors

	TrackView (Project* p);

	~TrackView ();

private: // signal handlers

	void on_track_added (Track*);

	void on_track_removed (Track*);

private: // member data

	TrackViewData* m_data;

};

} // namespace ui

#endif
