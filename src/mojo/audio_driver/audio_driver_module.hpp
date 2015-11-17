#ifndef MOJO_AUDIO_DRIVER_MODULE_H
#define MOJO_AUDIO_DRIVER_MODULE_H

/**
 *
 */
class AudioDriverModule : public Module {
public: // ctors
	virtual ~AudioDriverModule();

public: // Module interface
	virtual std::string get_author() = 0;

	virtual std::string get_description() = 0;

	virtual std::string get_version() = 0;

public: // interface
	virtual AudioDriverSP create_driver() const = 0;

protected: // ctors
	AudioDriverModule();
};

#endif // MOJO_AUDIO_DRIVER_MODULE_H
