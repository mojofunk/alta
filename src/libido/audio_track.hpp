
#ifndef LIBIDO_AUDIO_TRACK_INCLUDED
#define LIBIDO_AUDIO_TRACK_INCLUDED

#include <string>

#include <libido/types.hpp>
#include <libido/object.hpp>

namespace ido {

/**
 */
class IAudioTrack : public IObject
{
public:

	virtual const std::string& get_name() const = 0;

	virtual bool set_name(const std::string& name) = 0;

};

} // namespace ido

#endif
