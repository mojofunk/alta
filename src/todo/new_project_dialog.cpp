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

#include "new_project_dialog.hpp"

namespace gmojo {

std::string NewProjectDialogFactory::m_widget_name = "new_project_dialog";


Glib::RefPtr<Gnome::Glade::Xml>
NewProjectDialogFactory::create()
{
    return GladeFactory::create(GladePath::path("new_project_dialog.glade"));
}

NewProjectDialog::NewProjectDialog(BaseObjectType* cobject,
				   const Glib::RefPtr<Gnome::Glade::Xml>& xml)
    : Gtk::Dialog(cobject)
{
    xml->get_widget("new_project_template_file_chooser_button", m_template_file_chooser_button);
    
    /**
       
    */
    
}

bool
NewProjectDialog::use_project_template() const
{
    if(m_template_file_chooser_button->get_filename() == "") return false;
    return true;
}

Glib::ustring
NewProjectDialog::project_template_name() const
{
    return m_template_file_chooser_button->get_filename();
    
}

} // namespace gmojo

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
