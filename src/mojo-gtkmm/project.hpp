
#ifndef UI_PROJECT_INCLUDED
#define UI_PROJECT_INCLUDED

#include <sigc++/trackable.h>

namespace ui {

class Project : public sigc::trackable
{
public:

	Project ();

	void save ();

};

} // namespace ui

#endif
