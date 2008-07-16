
#ifndef JACK_AUDIO_DRIVER_MODULE
#define JACK_AUDIO_DRIVER_MODULE

#include <mojo/audio_driver_module.hpp>

namespace mojo {

class JACKAudioDriverModule : public AudioDriverModule
{
public: // constructors

	JACKAudioDriverModule();
	~JACKAudioDriverModule();

public: // Module interface

	virtual std::string get_author ();

	virtual std::string get_description ();

	virtual std::string get_version ();

public: // AudioDriverModule interface

	Devices get_devices () const;

private: // member data


};

} // namespace mojo

#endif
