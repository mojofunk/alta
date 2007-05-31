
#include <ui/edit_window_menu_ui_definition.hpp>

namespace gmojo {

const char* const edit_window_menu_ui_definition =
"<ui>" \
"  <menubar name=\"MainMenuBar\">" \
"     <menu name=\"FileMenu\" action=\"File\">" \
"        <menuitem name=\"NewProjectMenu\" action=\"NewProject\" />" \
"        <menuitem name=\"CloseProjectMenu\" action=\"CloseProject\" />" \
"        <menuitem name=\"QuitProjectMenu\" action=\"Quit\" />" \
"     </menu>" \
"     <menu name=\"EditMenu\" action=\"Edit\">" \
"     </menu>" \
"     <menu name=\"ViewMenu\" action=\"View\">" \
"     </menu>" \
"     <menu name=\"HelpMenu\" action=\"Help\">" \
"     </menu>" \
"  </menubar>" \
"</ui>";

} // namespace gmojo