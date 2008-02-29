
#include <ui/actions/app_actions.hpp>

namespace gmojo {

void new_project(GtkAction* action, App* app)
{
	App::new_project();
}

void quit(GtkAction* action, App* app)
{
	App::quit();
}

} // namespace gmojo
