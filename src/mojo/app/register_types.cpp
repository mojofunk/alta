
#include <mojo/typesystem/type_system.hpp>
#include <mojo/typesystem/template_type_factory.hpp>

#include <mojo/objects/object_collection.hpp>
#include <mojo/objects/audio_track.hpp>
#include <mojo/objects/midi_track.hpp>
#include <mojo/objects/audio_sequence.hpp>
#include <mojo/objects/audio_event.hpp>

#include "register_types.hpp"
#include "type_names.hpp"

namespace mojo {

void
register_types()
{
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<int32_t>(int32_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<int64_t>(int64_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<float>(float_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<std::string>(string_type_name)));

	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<ObjectCollection>(collection_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<ObjectSP>(object_ref_type_name)));

	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<AudioTrack>(audio_track_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<MidiTrack>(midi_track_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<AudioSequence>(audio_sequence_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<AudioEvent>(audio_event_type_name)));
}

} // namespace mojo
