
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

private:

	Gtk::HPaned m_hpaned;

};

} // namespace ui

#endif
