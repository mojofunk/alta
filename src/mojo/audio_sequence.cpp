#include <mojo/audio_sequence.hpp>
#include <mojo/object_collection.hpp>

#include <mojo/audio_event.hpp>

namespace mojo {

const char * const AudioSequence::s_property_audio_events = "audio-events";

AudioSequence::AudioSequence ()
{

}

void
AudioSequence::get_properties (Properties& props) const
{
	props.insert (make_property (s_property_audio_events, ObjectCollection(m_audio_events)));
}

void
AudioSequence::set_properties (const Properties& props)
{

}

std::pair<AudioSequence::iterator, bool>
AudioSequence::insert (AudioEventSPtr ae)
{
	return m_audio_events.insert (ae);
}

AudioSequence::size_type
AudioSequence::erase (AudioEventSPtr ae)
{
	return m_audio_events.erase (ae);
}

} // namespace mojo
