
#ifndef GMOJO_TRACK_CONTROL_INCLUDED
#define GMOJO_TRACK_CONTROL_INCLUDED

#include <ui/widget.hpp>

namespace gmojo {

class TrackControl : public Widget
{
public:

	virtual ~TrackControl() { }

	virtual GtkWidget* get_widget() const = 0;

};

} // namespace gmojo

#endif
