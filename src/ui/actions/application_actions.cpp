
#include <ui/actions/application_actions.hpp>

namespace gmojo {

void new_project(GtkAction* action, Application* app)
{
	app->new_project();
}

void quit(GtkAction* action, Application* app)
{
	app->quit();
}

} // namespace gmojo
