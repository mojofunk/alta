#ifndef UI_TRANSPORT_TOOLBAR_FACTORY
#define UI_TRANSPORT_TOOLBAR_FACTORY

#include "transport_toolbar.hpp"

namespace ui {

class Project;

class TransportToolbarFactory
{
public:
	static TransportToolbar* create (mojo::Project* proj);
};

} // namespace ui

#endif
