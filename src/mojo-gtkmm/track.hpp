
#ifndef UI_TRACK
#define UI_TRACK

#include <sigc++/trackable.h>

namespace ui {

class Track : public sigc::trackable
{
public:

	virtual ~Track () { }

};

} // namespace ui

#endif
