
#ifndef MOJO_APPLICATION_AMALGAMATED
#include "audio_clip.hpp"
#include "audio_region.hpp"
#endif

namespace mojo {

const char * const AudioRegion::s_property_audio_clip = "audioclip";
const char * const AudioRegion::s_property_offset = "offset";
const char * const AudioRegion::s_property_duration = "duration";

AudioRegion::AudioRegion ()
{

}

AudioRegion::AudioRegion (const count_t& offset, const count_t& dur)
{

}

void
AudioRegion::get_properties (Properties& props) const
{
	props.set_property (s_property_audio_clip, m_audio_clip);
	props.set_property (s_property_offset, m_offset);
	props.set_property (s_property_duration, m_duration);
}

void
AudioRegion::set_properties (const Properties& props)
{

}

} // namespace mojo
