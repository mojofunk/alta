
#ifndef MOJO_APPLICATION_AMALGAMATED

#include "mojo/core/object/object_collection.hpp"

#include "audio_sequence.hpp"
#include "audio_event.hpp"
#endif

namespace mojo {

const char * const AudioSequence::s_property_audio_events = "audio-events";

AudioSequence::AudioSequence ()
{

}

void
AudioSequence::get_properties (Properties& props) const
{
	props.set_property (s_property_audio_events, m_audio_events);
}

void
AudioSequence::set_properties (const Properties& props)
{

}

std::pair<AudioSequence::iterator, bool>
AudioSequence::insert (AudioEventSP ae)
{
	return m_audio_events.insert (ae);
}

AudioSequence::size_type
AudioSequence::erase (AudioEventSP ae)
{
	return m_audio_events.erase (ae);
}

} // namespace mojo
