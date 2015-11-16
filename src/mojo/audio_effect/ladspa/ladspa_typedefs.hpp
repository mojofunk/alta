#ifndef MOJO_LADSPA_TYPEDEFS_H
#define MOJO_LADSPA_TYPEDEFS_H

namespace mojo {
typedef std::shared_ptr<LADSPAAudioEffectInfo> LADSPAAudioEffectInfoSP;
typedef std::weak_ptr<LADSPAAudioEffectInfo> LADSPAAudioEffectInfoWPtr;
}

#endif
