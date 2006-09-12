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

#ifndef MOJO_PROJECT_HPP
#define MOJO_PROJECT_HPP

#include <string>

#include <sigc++/sigc++.h>

//#include <glibmmx/glibmmx.h>

namespace mojo {

/*
  the Idea for the Project class
  is the be sort of like the ARDOUR::session
  class but moving as much functionality into
  subclasses and if possible have public
  accessors to the subclass objects so that
  the subclasses are accessed directly(via 
  reference) and the Project class doesn't 
  need wrapper functions.
  
*/
class Project : public sigc::trackable
{
public:
    
    /**
       path to project 
    */
    //const std::string& path() { return m_path; }
    
    
    /**
       
    */
    Project();

    ~Project();
    
    Transport& transport() { return m_transport; }


protected:

    Transport& m_transport;
    
    /// path to project file.
    //const std::string m_path;
    
    
};

} // namespace mojo

#endif // MOJO_PROJECT_HPP

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
