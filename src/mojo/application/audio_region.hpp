#ifndef MOJO_AUDIO_REGION_H
#define MOJO_AUDIO_REGION_H

/**
 * An AudioRegion is a section within a clip with an offset and duration
 * and a snap point.
 */
class AudioRegion : public Object {
public:
	AudioRegion();

	AudioRegion(const count_t& offset, const count_t& dur);

public:
	// Object interface
	virtual void get_properties(Properties& props) const;

	virtual void set_properties(const Properties& props);

public:
	// AudioClipSP get_clip ();

	// void set_clip (AudioClipSP ac);

private:
	AudioClipSP m_audio_clip;

	count_t m_offset;
	count_t m_duration;

private:
	// property names
	static const char* const s_property_audio_clip;
	static const char* const s_property_offset;
	static const char* const s_property_duration;
};

#endif // MOJO_AUDIO_REGION_H
