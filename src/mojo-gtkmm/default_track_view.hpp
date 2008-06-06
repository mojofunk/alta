
#ifndef UI_DEFAULT_TRACK_VIEW
#define UI_DEFAULT_TRACK_VIEW

#include <gtkmm/paned.h>

#include "track_view.hpp"

namespace ui {

class DefaultTrackView : public TrackView
{
public:

	DefaultTrackView (Project*);

private:

	virtual void on_track_added (Track*);

	virtual void on_track_removed (Track*);

private:

	Gtk::HPaned m_hpaned;

};

} // namespace ui

#endif
