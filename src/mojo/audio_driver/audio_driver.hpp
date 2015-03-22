#ifndef MOJO_AUDIO_DRIVER_H
#define MOJO_AUDIO_DRIVER_H

#include "mojo-audio-driver.hpp"

namespace mojo {

class AudioDriver 
{
public: // ctors

	virtual ~AudioDriver ();

public: // interface

	virtual AudioDeviceSPSet get_devices () const = 0;

protected: // ctors

	AudioDriver ();

};

} // namespace mojo

#endif // MOJO_AUDIO_DRIVER_H
