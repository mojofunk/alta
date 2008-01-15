
#ifndef MOJO_AUDIO_REGION_EVENT_INCLUDED
#define MOJO_AUDIO_REGION_EVENT_INCLUDED

#include <mojo/audio_event.hpp>
#include <mojo/audio_region_ptr.hpp>

namespace mojo {

class AudioRegionEvent : public AudioEvent
{
public:

	AudioRegionEvent ();

	AudioRegionEvent (const count_t& pos, const count_t& dur);

public:

	// Object interface
	virtual void get_properties (Properties& props) const;

	virtual void set_properties (const Properties& props);

public:

	//AudioRegionSPtr get_region ();

	//void set_region (AudioRegionSPtr ar);

private:

	AudioRegionSPtr  m_audio_region;

private:

	static const char * const s_property_audio_region;

};

} // namespace mojo

#endif
