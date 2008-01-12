#include <mojo/audio_sequence.hpp>

namespace mojo {

const char * const AudioSequence::s_property_audio_events = "audio-events";

AudioSequence::AudioSequence ()
{

}

void
AudioSequence::get_property (const std::string& name, boost::any& value) const
{
	if (name == s_property_audio_events) {
		value = m_audio_events;
	}
}

void
AudioSequence::set_property (const std::string& name, const boost::any& value)
{

}

std::vector<std::string>
AudioSequence::get_property_names () const
{
	std::vector<std::string> property_names;

	property_names.push_back (s_property_audio_events);

	return property_names;
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
