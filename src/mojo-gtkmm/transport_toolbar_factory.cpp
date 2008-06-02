
#include "transport_toolbar_factory.hpp"

#include "default_transport_toolbar.hpp"

namespace ui {

TransportToolbar*
TransportToolbarFactory::create (Project* proj)
{
	return new DefaultTransportToolbar (proj);
}

} // namespace ui
