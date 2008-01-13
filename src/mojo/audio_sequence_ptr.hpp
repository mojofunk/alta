
#ifndef MOJO_AUDIO_SEQUENCE_PTR_INCLUDED
#define MOJO_AUDIO_SEQUENCE_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class AudioSequence;

	typedef boost::shared_ptr<AudioSequence>    AudioSequenceSPtr;
	typedef boost::weak_ptr<AudioSequence>      AudioSequenceWPtr;

} // namespace mojo

#endif
