
#ifndef MOJO_AUDIO_REGION_INCLUDED
#define MOJO_AUDIO_REGION_INCLUDED

#include <mojo/types.hpp>
#include <mojo/object.hpp>

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

	count_t	                      m_offset;
	count_t                       m_duration;

private:

	// property names
	static const char * const s_property_offset;
	static const char * const s_property_duration;
};

} // namespace mojo

#endif
