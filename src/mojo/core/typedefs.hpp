
#ifndef MOJO_CORE_TYPEDEFS
#define MOJO_CORE_TYPEDEFS

#include "macros.hpp"
#include "forward.hpp"

namespace mojo {

MOJO_DEFINE_POINTER_TYPEDEFS(Archive)
MOJO_DEFINE_POINTER_TYPEDEFS(ArchiveModule)
MOJO_DEFINE_POINTER_TYPEDEFS(AudioDevice)
MOJO_DEFINE_POINTER_TYPEDEFS(AudioDriverModule)
MOJO_DEFINE_POINTER_TYPEDEFS(AudioEffect)
MOJO_DEFINE_POINTER_TYPEDEFS(AudioEffectInfo)
MOJO_DEFINE_POINTER_TYPEDEFS(AudioEffectModule)
MOJO_DEFINE_POINTER_TYPEDEFS(AudioEffectParameterInfo)
MOJO_DEFINE_POINTER_TYPEDEFS(AudioFile)
MOJO_DEFINE_POINTER_TYPEDEFS(AudioFileModule)
MOJO_DEFINE_POINTER_TYPEDEFS(AudioFileFormat)
MOJO_DEFINE_POINTER_TYPEDEFS(Module)
	
MOJO_DEFINE_POINTER_SET_TYPEDEFS(ArchiveModule)
MOJO_DEFINE_POINTER_SET_TYPEDEFS(AudioDriverModule)
MOJO_DEFINE_POINTER_SET_TYPEDEFS(AudioEffectModule)
MOJO_DEFINE_POINTER_SET_TYPEDEFS(AudioFileModule)
MOJO_DEFINE_POINTER_SET_TYPEDEFS(Module)

MOJO_DEFINE_POINTER_SET_TYPEDEFS(AudioDevice)
MOJO_DEFINE_POINTER_SET_TYPEDEFS(AudioFileFormat)
MOJO_DEFINE_POINTER_SET_TYPEDEFS(AudioEffectInfo)

} // namespace mojo

#endif
