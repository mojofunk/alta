
#ifndef EDITOR_CANVAS_HPP
#define EDITOR_CANVAS_HPP

#include <list>

#include "project_view.hpp"

//#include "canvas_properties.hpp"

namespace gmojo {

/**
   The editor canvas contains the various views
   of objects such as audio tracks busses and 
   automation.

   needs access to the SessionView so when a 
   new session object is created that has a 
   time axis representaion it can be displayed.

*/
class EditorCanvas
{
public:
    
    EditorCanvas(ProjectView&);
    
protected:
    
    // std::list<TimeAxisView*> m_views;

    ProjectView& m_project_view;

};

} // namespace gmojo

#endif // EDITOR_CANVAS_HPP
