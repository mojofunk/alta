
#ifndef GMOJO_TRACK_CONTROL_INCLUDED
#define GMOJO_TRACK_CONTROL_INCLUDED

#include <ui/gtk/widget.hpp>

namespace gmojo {

class TrackControl : public gtk::Widget
{
public:

	virtual ~TrackControl();

	virtual GtkWidget* get_widget() = 0;

};

} // namespace gmojo

#endif // GMOJO_TRACK_CONTROL_INCLUDED
