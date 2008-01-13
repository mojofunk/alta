
#include <mojo/audio_track.hpp>
#include <mojo/audio_sequence.hpp>
#include <mojo/object_ptr.hpp>

namespace mojo {

const char * const AudioTrack::s_property_audio_sequence = "audio-sequence";

AudioTrack::AudioTrack()
	:
		m_audio_sequence (new AudioSequence)
{

}

void
AudioTrack::get_property (const std::string& name, boost::any& value) const
{
	Track::get_property (name, value);

	if (name == s_property_audio_sequence)
	{
		value = ObjectSPtr(m_audio_sequence);
		return;
	}
}

void
AudioTrack::set_property (const std::string& name, const boost::any& value)
{
	Track::set_property (name, value);

}

std::vector<std::string>
AudioTrack::get_property_names () const
{
	std::vector<std::string> names = Track::get_property_names ();
	names.push_back ( s_property_audio_sequence );

	return names;
}

AudioSequenceSPtr
AudioTrack::get_audio_sequence ()
{
	return m_audio_sequence;
}

} // namespace mojo
