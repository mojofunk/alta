#ifndef MOJO_AUDIO_EVENT_INCLUDED
#define MOJO_AUDIO_EVENT_INCLUDED

#include <mojo/event.hpp>

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

}

#endif
