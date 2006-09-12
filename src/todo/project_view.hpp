/*
  Copyright (C) 2005 Tim Mayberry
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
  
  $Id$
*/

#ifndef PROJECT_VIEW_HPP
#define PROJECT_VIEW_HPP

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

    sigc::signal<void>&
    visibility_changed() { return m_visibility_changed; }

protected:

    sigc::signal<void> m_visibility_changed;    


    mojo::Project* m_project;	
    
    EditorView m_editor;
    
    //Mixer m_mixer;
    
    //TransportControl m_transport_control;
    
};

} // namespace gmojo

#endif // PROJECT_VIEW_HPP

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:encoding=utf-8:textwidth=99 :
