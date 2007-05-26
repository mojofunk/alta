
#include <ui/gtk_ui_manager.hpp>

namespace gtk {

boost::intrusive_ptr<GtkUIManager>
ui_manager_factory()
{
	// false indicates not to take a reference as
	// the reference count is already 1.
	return boost::intrusive_ptr<GtkUIManager>(gtk_ui_manager_new(), false);
}

} // namespace gtk
