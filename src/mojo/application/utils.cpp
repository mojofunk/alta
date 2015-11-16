namespace mojo {

std::string track_type_to_string(TrackType type)
{
	if (type == AUDIO) {
		return "Audio";
	} else if (type == MIDI) {
		return "Midi";
	}

	// error
	return "Unknown Track Type";
}

} // namespace mojo
