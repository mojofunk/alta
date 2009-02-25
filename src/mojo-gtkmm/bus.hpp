
#ifndef UI_BUS
#define UI_BUS

#include <mojo/mojo.hpp>

namespace ui {

/*
 * The Bus class ensures that signals emitted
 * by the Session class are reemitted in the
 * in the GUI thread.
 */
class Bus : public mojo::SessionBus
{
public:

	Bus ();
	~Bus ();

protected:

	virtual void on_project_added (mojo::Project*);

	virtual void on_project_removed (mojo::Project*);

	virtual void on_project_saved ();

	virtual void on_track_added (mojo::Track*);

	virtual void on_track_removed (mojo::Track*);

};

} // namespace ui

#endif
