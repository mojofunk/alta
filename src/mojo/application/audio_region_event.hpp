#ifndef MOJO_AUDIO_REGION_EVENT_H
#define MOJO_AUDIO_REGION_EVENT_H

#ifndef MOJO_APPLICATION_AMALGAMATED
#include "typedefs.hpp"
#include "audio_event.hpp"
#endif

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

	//AudioRegionSP get_region ();

	//void set_region (AudioRegionSP ar);

private:

	AudioRegionSP  m_audio_region;

private:

	static const char * const s_property_audio_region;

};

} // namespace mojo

#endif // MOJO_AUDIO_REGION_EVENT_H
