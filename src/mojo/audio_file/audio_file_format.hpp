#ifndef MOJO_AUDIO_FILE_FORMAT_H
#define MOJO_AUDIO_FILE_FORMAT_H

class AudioFileFormat
{
public:
	virtual ~AudioFileFormat();

	virtual std::string name() const = 0;

	virtual std::string extension() const = 0;

protected:
	AudioFileFormat();
};

#endif // MOJO_AUDIO_FILE_FORMAT_H
