
#include "bus.hpp"
#include "session.hpp"
#include "session_data.hpp"

namespace mojo {

void
Session::new_project_async ()
{
	project_t p;

	for (std::set<Bus*>::iterator i = data->busses.begin();
			i != data->busses.end(); ++i)
	{
		(*i)->on_project_added (p);
	}
}

} // namespace mojo
