
#ifndef MOJO_SNDFILE_AUDIO_FILE_FORMAT_INCLUDED
#define MOJO_SNDFILE_AUDIO_FILE_FORMAT_INCLUDED

#include <mojo/audio_file_format.hpp>

namespace mojo {

class SndfileAudioFileFormat : public AudioFileFormat
{
public: // constructors

	// @param format The major and minor format
	SndfileAudioFileFormat(int sndfile_format);

public: // AudioFileFormat interface

	string name() const;

	string extension() const;

public: // member functions

	int format () const;

private: // member data

	const int m_format;

};

} // namespace mojo

#endif
