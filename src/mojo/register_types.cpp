
#include <typeinfo>

#include <mojo/register_types.hpp>
#include <mojo/type_system.hpp>
#include <mojo/type_names.hpp>
#include <mojo/type_template.hpp>

#include <mojo/audio_track.hpp>
#include <mojo/audio_track_ptr.hpp>

namespace mojo {

void
register_types()
{
	register_type (TypeSPtr(new TypeTemplate<int>(int_type_name)));
	register_type (TypeSPtr(new TypeTemplate<float>(float_type_name)));
	register_type (TypeSPtr(new TypeTemplate<std::string>(string_type_name)));

	register_type (TypeSPtr(new TypeTemplate<AudioTrackSPtr>(audio_track_type_name)));
}

}
