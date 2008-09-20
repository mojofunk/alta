
#include "audio_region.hpp"
#include "audio_region_event.hpp"

namespace mojo {

const char * const AudioRegionEvent::s_property_audio_region = "audioregion";

AudioRegionEvent::AudioRegionEvent () : AudioEvent() { }

AudioRegionEvent::AudioRegionEvent (const count_t& pos, const count_t& dur)
	:
		AudioEvent(pos, dur)
{

}

void
AudioRegionEvent::get_properties (Properties& props) const
{
	AudioEvent::get_properties (props);

	props.insert (make_property (s_property_audio_region, ObjectSP(m_audio_region)));
}

void
AudioRegionEvent::set_properties (const Properties& props)
{

}

} // namespace mojo
