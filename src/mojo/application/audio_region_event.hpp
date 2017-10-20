#ifndef MOJO_AUDIO_REGION_EVENT_H
#define MOJO_AUDIO_REGION_EVENT_H

class AudioRegionEvent : public AudioEvent
{
public:
	AudioRegionEvent();

	AudioRegionEvent(const count_t& pos, const count_t& dur);

public:
	// Object interface
	virtual void get_properties(Properties& props) const;

	virtual void set_properties(const Properties& props);

public:
	// AudioRegionSP get_region ();

	// void set_region (AudioRegionSP ar);

private:
	AudioRegionSP m_audio_region;

private:
	static const char* const s_property_audio_region;
};

#endif // MOJO_AUDIO_REGION_EVENT_H
