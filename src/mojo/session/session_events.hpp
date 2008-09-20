
#ifndef MOJO_SESSION_EVENTS
#define MOJO_SESSION_EVENTS

namespace mojo {

/**
 *
 */
enum SessionEventType {
	PropertyChange,
	TransportStateChange,
	ProjectOpened,
	ProjectClosed,
	ProjectSaved,
	AudioDeviceChange
};

} // namespace mojo

#endif
