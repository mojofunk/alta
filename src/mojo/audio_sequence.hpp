#ifndef MOJO_AUDIO_SEQUENCE_INCLUDED
#define MOJO_AUDIO_SEQUENCE_INCLUDED

#include <mojo/audio_event.hpp>
#include <mojo/audio_event_ptr.hpp>

#include <set>

namespace mojo {

class AudioSequence
{
public:

	void add (AudioEventSPtr ae);

private:

	std::set<AudioEventSPtr> m_audio_events;

};

}

#endif
