
#ifndef UI_BUS
#define UI_BUS

#include <mojo/mojo.hpp>

namespace ui {

class Bus : public mojo::SessionBus
{
public:

	Bus ();
	~Bus ();

protected:

	virtual void on_project_added (mojo::Project*);

	virtual void on_project_removed (mojo::Project*);

	virtual void on_project_saved ();

};

} // namespace ui

#endif
