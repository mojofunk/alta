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

#ifndef GMOJO_GUI_HPP
#define GMOJO_GUI_HPP

#include <gtkmm.h>

#include "project.hpp"

#include "timers.hpp"
#include "project_view.hpp"
#include "new_project_dialog.hpp"

namespace gmojo {

class gui : public sigc::trackable
{
public:
    
    static gui& instance() { return *s_m_gui;}
    
    //  static GlibX::Dispatcher& dispatcher() { return m_gui->m_disp; }
    
    static void create(int argc, char *argv[]);
    
    virtual void run();
    
    /**
      must check the state of each open project,
      if state is dirty then ask the user if they
      want to save the project.
    */
    virtual void quit();
    
    virtual ~gui();
    
    Timers& timers() { return m_timers; }
    
    sigc::signal<void, bool>&
    signal_accel_assign() { return m_accel_assign; }
    
    /// all new projects are created in a 
    /// temp directory
    /// activate new project dialogue.
    void new_project();
    
    /// activate open project dialogue.
    void open_project();
    
protected:

    gui(int argc, char *argv[]);

    void open_project(const std::string& path_to_file);
    
    //    GlibX::GlibDispatcher m_disp;
    
    static gui* s_m_gui;
    
    Gtk::Main  m_main_loop;

    Timers m_timers;

    sigc::signal<void, bool> m_accel_assign;
    
    /**
       map path of project file to projectviews
       so that we don't bother trying
       to open a project twice amoungst other things.
    */
    std::map<std::string,ProjectView*> project_map;
        
    /// project agnostic top level dialogs

    Glib::RefPtr<Gnome::Glade::Xml> m_new_project_dialog_glade_ref;
    NewProjectDialog* m_new_project_dialog;
    // about dialog
    // preferences dialog
    // tool

    // edit buffer cut/paste


};

} // namespace gmojo

#endif // GMOJO_GUI_HPP

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
