
#ifndef MOJO_AUDIO_EFFECT
#define MOJO_AUDIO_EFFECT

#include "typedefs.hpp"

namespace mojo {

class AudioEffect
{
public:

	typedef std::set<uint32_t> ParameterList;

public: // constructors

	virtual ~AudioEffect ();

public: // AudioEffect interface

	virtual AudioEffectInfoSPtr get_info () const = 0;

	//virtual uint32_t get_input_count () const = 0;

	//virtual uint32_t get_output_count () const = 0;

	virtual ParameterList get_parameter_list () const = 0;

	virtual void get_parameter_info (uint32_t param_id, AudioEffectParameterInfo& info) const = 0;

	virtual float get_parameter (uint32_t param_id) const = 0;

	virtual void set_parameter (uint32_t param_id, float value) = 0;

	virtual void activate () = 0;

	virtual void deactivate () = 0;

	virtual void set_block_size (uint32_t frames) = 0;

};

} // namespace mojo

#endif
