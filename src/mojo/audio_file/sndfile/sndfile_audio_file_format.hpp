#ifndef MOJO_SNDFILE_AUDIO_FILE_FORMAT_H
#define MOJO_SNDFILE_AUDIO_FILE_FORMAT_H

namespace mojo {

class SndfileAudioFileFormat : public AudioFileFormat {
public: // constructors
	// @param format The major and minor format
	SndfileAudioFileFormat(int sndfile_format);

public: // AudioFileFormat interface
	string name() const;

	string extension() const;

public: // member functions
	int format() const;

private: // member data
	const int m_format;
};

} // namespace mojo

#endif
