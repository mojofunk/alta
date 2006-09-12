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

#ifndef TIME_AXIS_VIEW_HPP
#define TIME_AXIS_VIEW_HPP

#include <gtkmm.h>
#include <libgnomecanvasmm/libgnomecanvasmm.h>

#include "view.hpp"
#include "selectable.hpp"
//#include "visibility_group.hpp"

namespace gmojo {

/**
   TimeAxisView defines the abstract base class for
   time-axis views.

   this will be a statefull object.

*/
class TimeAxisView
: public View, public Selectable, public Gnome::Canvas::Group
{
public:

	TimeAxisView(const Gnome::Canvas::Group& parent);
	
	virtual ~TimeAxisView ();

	const Glib::ustring& name() = 0;
	
	virtual void set_height(double new_height);
	virtual double height() const;
	
	/// @see View
	void set_visible(bool yn);
	
	sigc::signal<void>&
	visibility_changed() { return m_visibility_changed; }

	/// @see Selectable
	virtual void set_selected (bool);
	
	virtual void show_selection (AudioRange&);
	virtual void hide_selection ();

	virtual void set_samples_per_unit (double);

	// must be emitted in destructor.
	virtual sigc::signal<void>& signal_destroyed() = 0;

protected:
    
    SelectionRect m_selection_rect;

	sigc::signal<void> m_visibility_changed;

};

} // namespace gmojo

#endif // TIME_AXIS_VIEW_HPP

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
