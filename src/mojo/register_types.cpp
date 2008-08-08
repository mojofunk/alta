
#include <typeinfo>

#include <mojo/typesystem/type_system.hpp>
#include <mojo/typesystem/template_type_factory.hpp>

#include <mojo/register_types.hpp>
#include <mojo/type_names.hpp>

#include <mojo/object_collection.hpp>

#include <mojo/audio_track.hpp>
#include <mojo/midi_track.hpp>
#include <mojo/audio_sequence.hpp>
#include <mojo/audio_event.hpp>

namespace mojo {

void
register_types()
{
	TypeSystem::register_type (TypeFactorySPtr(new TemplateTypeFactory<int32_t>(int32_type_name)));
	TypeSystem::register_type (TypeFactorySPtr(new TemplateTypeFactory<int64_t>(int64_type_name)));
	TypeSystem::register_type (TypeFactorySPtr(new TemplateTypeFactory<float>(float_type_name)));
	TypeSystem::register_type (TypeFactorySPtr(new TemplateTypeFactory<std::string>(string_type_name)));

	TypeSystem::register_type (TypeFactorySPtr(new TemplateTypeFactory<ObjectCollection>(collection_type_name)));
	TypeSystem::register_type (TypeFactorySPtr(new TemplateTypeFactory<ObjectSPtr>(object_ref_type_name)));

	TypeSystem::register_type (TypeFactorySPtr(new TemplateTypeFactory<AudioTrack>(audio_track_type_name)));
	TypeSystem::register_type (TypeFactorySPtr(new TemplateTypeFactory<MidiTrack>(midi_track_type_name)));
	TypeSystem::register_type (TypeFactorySPtr(new TemplateTypeFactory<AudioSequence>(audio_sequence_type_name)));
	TypeSystem::register_type (TypeFactorySPtr(new TemplateTypeFactory<AudioEvent>(audio_event_type_name)));
}

}
