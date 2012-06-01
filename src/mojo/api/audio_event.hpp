#ifndef MOJO_AUDIO_EVENT
#define MOJO_AUDIO_EVENT

#include "event.hpp"

namespace mojo {

class AudioEvent : public Event
{
public:

	AudioEvent();

	AudioEvent(const count_t& pos, const count_t& dur);

public:

	// Object interface
	virtual void get_properties (Properties& props) const;

	virtual void set_properties (const Properties& props);

};

} // namespace mojo

#endif
