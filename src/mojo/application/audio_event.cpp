
#ifndef MOJO_AMALGAMATED
#include "audio_event.hpp"
#endif

namespace mojo {

AudioEvent::AudioEvent()
    : Event()
{
}

AudioEvent::AudioEvent(const count_t& pos, const count_t& dur)
    : Event(pos, dur)
{
}

void AudioEvent::get_properties(Properties& props) const
{
	Event::get_properties(props);
}

void AudioEvent::set_properties(const Properties& props)
{
}

} // namespace mojo
