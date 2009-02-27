
#include "transport_toolbar_factory.hpp"

#include "default_transport_toolbar.hpp"

namespace ui {

TransportToolbar*
TransportToolbarFactory::create (mojo::Project* proj)
{
	return new DefaultTransportToolbar (proj);
}

} // namespace ui
