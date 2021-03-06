#ifndef MOJO_TYPE_NAMES_H
#define MOJO_TYPE_NAMES_H

class MOJO_API TypeNames
{
public:
	static const char* const int32_type_name;
	static const char* const int64_type_name;
	static const char* const float_type_name;
	static const char* const string_type_name;

	// containers
	static const char* const collection_type_name;
	static const char* const object_ref_type_name;

	// TODO These shouldn't be here
	static const char* const audio_track_type_name;
	static const char* const midi_track_type_name;
	static const char* const audio_sequence_type_name;
	static const char* const audio_event_type_name;
};

#endif // MOJO_TYPE_NAMES_H
