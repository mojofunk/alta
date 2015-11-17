#ifndef MOJO_SNDFILE_AUDIO_FILE_FORMAT_H
#define MOJO_SNDFILE_AUDIO_FILE_FORMAT_H

class SndfileAudioFileFormat : public AudioFileFormat {
public: // constructors
	// @param format The major and minor format
	SndfileAudioFileFormat(int sndfile_format);

public: // AudioFileFormat interface
	std::string name() const;

	std::string extension() const;

public: // member functions
	int format() const;

private: // member data
	const int m_format;
};

#endif // MOJO_SNDFILE_AUDIO_FILE_FORMAT_H
