
#include <ui/application_commands.hpp>

namespace gmojo {

void file_new(GtkAction* action, Application* app)
{

	app->new_project();

}

} // namespace gmojo
