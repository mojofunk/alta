#ifndef MOJO_API_TYPES_H
#define MOJO_API_TYPES_H

enum Error {

};

enum TrackType { AUDIO, MIDI };

struct ImportOptions {
	bool copy_files;
	bool convert_samplerate;
	bool convert_samplesize;
	bool split_channels;
};

struct TrackOptions {
	TrackType type;
	uint8_t count;

	TrackOptions()
	    : type(AUDIO)
	    , count(1)
	{
	}

	TrackOptions(const TrackOptions& other)
	    : type(other.type)
	    , count(other.count)
	{
	}
};

#endif // MOJO_API_TYPES_H
