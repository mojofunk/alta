
#ifndef GMOJO_GTK_WIDGET_PTR_INCLUDED
#define GMOJO_GTK_WIDGET_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace gtk {

	class Widget;

	typedef boost::shared_ptr<Widget>    WidgetSPtr;
	typedef boost::weak_ptr<Widget>      WidgetWPtr;

} // namespace gtk

#endif
