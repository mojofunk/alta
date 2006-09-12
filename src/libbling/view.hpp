
#ifndef VIEW_HPP
#define VIEW_HPP

#include <sigc++/signal.h>

namespace gmojo {

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

} // namespace gmojo

#endif // VIEW_HPP

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
