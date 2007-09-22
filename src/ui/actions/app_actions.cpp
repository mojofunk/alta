
#include <ui/actions/app_actions.hpp>

namespace gmojo {

void new_project(GtkAction* action, App* app)
{
	app->new_project();
}

void quit(GtkAction* action, App* app)
{
	app->quit();
}

} // namespace gmojo
