
#include <mojo/audio_region_event.hpp>

namespace mojo {

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
}

void
AudioRegionEvent::set_properties (const Properties& props)
{

}

} // namespace mojo
