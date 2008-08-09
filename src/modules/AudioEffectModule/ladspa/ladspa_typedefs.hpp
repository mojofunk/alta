
#ifndef MOJO_LADSPA_TYPEDEFS
#define MOJO_LADSPA_TYPEDEFS

#include "ladspa_forward.hpp"

namespace mojo {

	typedef boost::shared_ptr<LADSPAAudioEffectInfo>  LADSPAAudioEffectInfoSPtr;
	typedef boost::weak_ptr<LADSPAAudioEffectInfo>    LADSPAAudioEffectInfoWPtr;

}

#endif
