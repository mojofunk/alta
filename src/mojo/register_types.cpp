
#include <typeinfo>

#include <mojo/register_types.hpp>
#include <mojo/type_system.hpp>
#include <mojo/type_names.hpp>
#include <mojo/template_type_factory.hpp>

#include <mojo/object_collection.hpp>

#include <mojo/audio_track.hpp>
#include <mojo/audio_track_ptr.hpp>

namespace mojo {

void
register_types()
{
	TypeSystem::register_type (TypeFactorySPtr(new TemplateTypeFactory<int>(int_type_name)));
	TypeSystem::register_type (TypeFactorySPtr(new TemplateTypeFactory<float>(float_type_name)));
	TypeSystem::register_type (TypeFactorySPtr(new TemplateTypeFactory<std::string>(string_type_name)));

	TypeSystem::register_type (TypeFactorySPtr(new TemplateTypeFactory<ObjectCollection>(collection_type_name)));

	TypeSystem::register_type (TypeFactorySPtr(new TemplateTypeFactory<AudioTrack>(audio_track_type_name)));

}

}
