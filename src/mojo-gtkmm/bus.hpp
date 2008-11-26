
#ifndef UI_BUS
#define UI_BUS

#include <mojo/mojo.hpp>

namespace ui {

class Bus : public mojo::Bus
{
public:

	Bus ();
	~Bus ();

protected:

	virtual void on_project_opened (mojo::Project*);

	virtual void on_project_closed ();

	virtual void on_project_saved ();

};

} // namespace ui

#endif
