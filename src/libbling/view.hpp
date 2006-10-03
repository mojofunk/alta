
#ifndef BLING_VIEW_INCLUDED
#define BLING_VIEW_INCLUDED

#include <sigc++/signal.h>

namespace bling {

/**
   The view class is a base class for classes
   that embody a visual representation of some
   object.
*/
class View
{
public:
    
    // m_visible must be set in derived
    // classes to reflect the actual default
    // visibility state when a class is created.
    View() : m_visible(true) { }
    
    virtual ~View() { }
    
    /// @return true if view is visible.
    virtual bool visible() const { return m_visible; }
    
    /// set the View to be visible or not.
    virtual void set_visible(bool yn) = 0; 	
    
    /// Notifies that visibility of view has changed.
    virtual sigc::signal<void>& visibility_changed() = 0;
    
protected:
    
    bool m_visible;
    
};

} // namespace bling

#endif // BLING_VIEW_INCLUDED
