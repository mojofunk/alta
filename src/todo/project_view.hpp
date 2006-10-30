
#ifndef GMOJO_PROJECT_VIEW_INCLUDED
#define GMOJO_PROJECT_VIEW_INCLUDED

#include <sigc++/signal.h>

#include "view.hpp"
#include "project.hpp"
#include "editor.hpp"
#include "object_color_map.hpp"

namespace gmojo {

/**
   The project view is intended to be the central
   class through which all the different Views of
   the project are created and accessed.

*/
class ProjectView : public View
{
public:
	
    ProjectView(mojo::Project* project);

    mojo::Project& project() { return *m_project; }

    void set_visible(bool);

    sigc::signal<void>
    visibility_changed() { return m_visibility_changed; }

protected:

    sigc::signal<void> m_visibility_changed;    

    mojo::Project* m_project;	
    
    EditorView m_editor;
    
    //Mixer m_mixer;
    
    //TransportControl m_transport_control;
    
};

} // namespace gmojo

#endif // GMOJO_PROJECT_VIEW_INCLUDED
