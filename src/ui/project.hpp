
#ifndef GMOJO_PROJECT_INCLUDED
#define GMOJO_PROJECT_INCLUDED

#include <ui/gtk/window_ptr.hpp>

namespace gmojo {

/**
   The project view is intended to be the central
   class through which all the different Views of
   the project are created and accessed. It also 
   manages the top level windows for a project
*/
class Project
{
public:

	Project ();

	~Project ();

public:

	void save ();

	void create_audio_track ();

public:


private:

	bool on_edit_window_delete_event ();

private:

	// per project windows

	gtk::WindowSPtr m_edit_window;

};

} // namespace gmojo

#endif // GMOJO_PROJECT_VIEW_INCLUDED
