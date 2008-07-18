
#ifndef MOJO_AUDIO_REGION
#define MOJO_AUDIO_REGION

#include <mojo/forward.hpp>
#include <mojo/object.hpp>
#include <mojo/typedefs.hpp>
#include <mojo/types.hpp>

namespace mojo {

class AudioRegion : public Object
{
public:

	AudioRegion ();

	AudioRegion (const count_t& offset, const count_t& dur);

public:

	// Object interface
	virtual void get_properties (Properties& props) const;

	virtual void set_properties (const Properties& props);

public:

	//AudioClipSPtr get_clip ();
	
	//void set_clip (AudioClipSPtr ac);

private:

	AudioClipSPtr                 m_audio_clip;

	count_t	                      m_offset;
	count_t                       m_duration;

private:

	// property names
	static const char * const s_property_audio_clip;
	static const char * const s_property_offset;
	static const char * const s_property_duration;
};

} // namespace mojo

#endif
