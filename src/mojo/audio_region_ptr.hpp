
#ifndef MOJO_AUDIO_REGION_PTR_INCLUDED
#define MOJO_AUDIO_REGION_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class AudioRegion;

	typedef boost::shared_ptr<AudioRegion>    AudioRegionSPtr;
	typedef boost::weak_ptr<AudioRegion>      AudioRegionWPtr;

} // namespace mojo

#endif
