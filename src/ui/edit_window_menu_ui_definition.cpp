
#include <ui/edit_window_menu_ui_definition.hpp>

namespace gmojo {

const char* const edit_window_menu_ui_definition =
"<ui>" \
"  <menubar name=\"MainMenuBar\">" \
"     <menu name=\"FileMenu\" action=\"File\">" \
"        <menuitem name=\"NewProjectMenu\" action=\"NewProject\" />" \
"        <menuitem name=\"SaveProjectMenu\" action=\"SaveProject\" />" \
"        <menuitem name=\"CloseProjectMenu\" action=\"CloseProject\" />" \
"        <menuitem name=\"CreateAudioTrackMenu\" action=\"CreateAudioTrack\" />" \
"        <menu name=\"ImportMenu\" action=\"Import\">" \
"            <menuitem name=\"CreateAudioTrackMenu\" action=\"CreateAudioTrack\" />" \
"        </menu>" \
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
