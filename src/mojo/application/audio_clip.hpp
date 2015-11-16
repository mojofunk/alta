#ifndef MOJO_AUDIO_CLIP_H
#define MOJO_AUDIO_CLIP_H

namespace mojo {

/**
 * A new AudioClip only references one audio file
 *
 * To support non-destructive editing of the audio file,
 * any processing of the original file results in a new
 * file being created.
 *
 * The AudioClip hides that it can be comprized of multiple
 * files.
 *
 * An AudioClip does not contain references to AudioFile instances
 * for each file that it references as that could mean exhausting
 * the number of open file descriptors available to the process.
 *
 * Processes such as Stretching, Shrinking and Pitch shifting
 * an AudioClip should use original audio sources rather than
 * using previously processed audio to create new audio
 * sources.
 *
 * How to write to AudioClip in buffer size chunks and
 * signal that a write has been completed?
 */
class AudioClip : public Object {
public:
	/**
	 * Create a new AudioClip from an existing audiofile
	 */
	AudioClip(const std::string& audiofile);

	AudioClip();

public:
	// Object interface
	virtual void get_properties(Properties& props) const;

	virtual void set_properties(const Properties& props);

private:
	std::string m_audiofile;
};

} // namespace mojo

#endif // MOJO_AUDIO_CLIP_H
