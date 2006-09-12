
#ifndef TRANSPORT_VIEW_HPP
#define TRANSPORT_VIEW_HPP

#include "view.hpp"

namespace gmojo {


/**
   The transport view will be a handlebox with a HBox as its
   child that contains two toolbars. The two toolbars are the
   normal transport controls and then another with all the 
   extended controls like pre-roll etc so they can be shown
   separately or packed differently etc.
*/
class TransportView : public View, public Gtk::HandleBox
{
public:

    /**
       TransportView is only dependant upon
       the transport class and not a project
       as a the transport class may not be
       destroyed with the project if two 
       projects are sharing the same transport.
    */
    TransportView(Transport& transport);

    ~TransportView();

    sigc::signal<void>& visibility_changed()
    { return m_visibility_changed; }

protected:

    sigc::signal<void> m_visibility_changed;

    mojo::Transport& m_transport;
    
    

};

} // namespace gmojo
