
#ifndef UI_TRACK_INCLUDED
#define UI_TRACK_INCLUDED

#include <sigc++/trackable.h>

namespace ui {

class Track : public sigc::trackable
{
public:

	virtual ~Track () { }

};

} // namespace ui

#endif
