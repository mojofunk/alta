
#ifndef GMOJO_GTK_WINDOW_PTR_INCLUDED
#define GMOJO_GTK_WINDOW_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace gtk {

	class Window;

	typedef boost::shared_ptr<Window>    WindowSPtr;
	typedef boost::weak_ptr<Window>      WindowWPtr;

} // namespace gtk

#endif
