
#include <ui/edit_window_menu_bar.hpp>

namespace {

const char* const menu_ui_string =
"<ui>" \
"  <menubar name=\"MainMenuBar\">" \
"     <menu name=\"FileMenu\" action=\"FileMenuAction\">" \
"        <menuitem name=\"New\" action=\"NewAction\" />" \
"        <menuitem name=\"Open\" action=\"OpenAction\" />" \
"     </menu>" \
"  </menubar>" \
"</ui>";

}

namespace gmojo {

EditWindowMenuBar::EditWindowMenuBar(boost::intrusive_ptr<GtkUIManager> ui_manager)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	guint merge_id = 0;
	GError * error = NULL;

	merge_id = gtk_ui_manager_add_ui_from_string (ui_manager.get(),
			menu_ui_string, -1, &error);

	if (merge_id == 0) {
		
#ifdef GMOJO_DEBUG
		LOG_GMOJO_CRITICAL << error->message;
#endif

		g_error_free(error);
		
		// throw 
	}

	m_menu_bar = gtk_ui_manager_get_widget(ui_manager.get(), "/MainMenuBar");

	if(!m_menu_bar)
	{

#ifdef GMOJO_DEBUG
		LOG_GMOJO_CRITICAL;
#endif
		// throw

	}

}


EditWindowMenuBar::~EditWindowMenuBar()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
}

} // namespace gmojo
