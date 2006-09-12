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

#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <gtkmm/window.h>

#include "transport_view.hpp"

namespace gmojo {

class Editor : public View, public Gtk::Window
{
public:
    
    Editor(mojo::Project& project);
    
    ~Editor();

protected:
    
    /// these are for menus etc.
    void on_menu_save();
    void on_menu_save_as();
    void on_menu_close();

    TransportView m_transport_view;

};

} // namespace gmojo
    
#endif // EDITOR_HPP

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
