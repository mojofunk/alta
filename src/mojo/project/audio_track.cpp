
#include "audio_track.hpp"
#include "audio_sequence.hpp"

namespace mojo {

const char * const AudioTrack::s_property_audio_sequence = "audio-sequence";

AudioTrack::AudioTrack()
	:
		m_audio_sequence (new AudioSequence)
{

}

void
AudioTrack::get_properties (Properties& props) const
{
	Track::get_properties (props);

	props.insert (make_property (s_property_audio_sequence, ObjectSP(m_audio_sequence)));
}

void
AudioTrack::set_properties (const Properties& props)
{
	Track::set_properties (props);

	// XXX
}

AudioSequenceSP
AudioTrack::get_audio_sequence ()
{
	return m_audio_sequence;
}

} // namespace mojo