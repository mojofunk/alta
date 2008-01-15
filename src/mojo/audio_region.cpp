
#include <mojo/object_ptr.hpp>
#include <mojo/audio_clip.hpp>

#include <mojo/audio_region.hpp>

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
	props.insert (make_property (s_property_audio_clip, ObjectSPtr(m_audio_clip)));
	props.insert (make_property (s_property_offset, m_offset));
	props.insert (make_property (s_property_duration, m_duration));
}

void
AudioRegion::set_properties (const Properties& props)
{

}

} // namespace mojo
