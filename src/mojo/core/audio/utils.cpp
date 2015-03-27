
#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"
#include "mojo/core/audio/utils.hpp"

#endif

namespace mojo {

std::vector<samplerate_t> get_common_samplerates()
{
	return { 44100, 48000, 88200, 96000, 176400, 192000 };
}

} // namespace mojo
