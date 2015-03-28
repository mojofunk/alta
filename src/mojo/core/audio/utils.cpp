
#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"
#include "mojo/core/audio/utils.hpp"

#endif

namespace mojo {

std::vector<samplerate_t> get_common_samplerates()
{
	return { 8000.0,  22050.0, 24000.0,  44100.0, 48000.0,
		        88200.0, 96000.0, 176400.0, 192000.0 };
}

} // namespace mojo
