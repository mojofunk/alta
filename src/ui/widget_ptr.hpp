
#ifndef GMOJO_GTK_WIDGET_PTR
#define GMOJO_GTK_WIDGET_PTR

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace gmojo {

	class Widget;

	typedef boost::shared_ptr<Widget>    WidgetSPtr;
	typedef boost::weak_ptr<Widget>      WidgetWPtr;

} // namespace gmojo

#endif
