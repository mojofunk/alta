
#ifndef MOJO_LADSPA_TYPEDEFS
#define MOJO_LADSPA_TYPEDEFS

#include "ladspa_forward.hpp"

namespace mojo {

typedef std::shared_ptr<LADSPAAudioEffectInfo> LADSPAAudioEffectInfoSP;
typedef std::weak_ptr<LADSPAAudioEffectInfo> LADSPAAudioEffectInfoWPtr;
}

#endif
