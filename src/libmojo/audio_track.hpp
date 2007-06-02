#ifndef MOJO_AUDIO_TRACK_INCLUDED
#define MOJO_AUDIO_TRACK_INCLUDED

#include <boost/signal.hpp>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>

#include <libmojo/object.hpp>

namespace mojo {

/**
 * An AudioTrack can contain:
 *
 * A sequence of audio events
 * A number of channels
 * A format type mono/stereo/etc
 * A Panner?
 *
 * An AudioTrack doesn't contain:
 *
 * The state of the connections to and from 
 * the track.
 */
class AudioTrack : public Object
{
public:

	AudioTrack ();
	
	const std::string&
		get_name () const { return m_name; }

	void set_name (const std::string& name);

	boost::signal<void ()>&
		signal_name_change () { return m_signal_name_change; }

private:
	
	friend class boost::serialization::access;

	template<class Archive>
		void serialize (Archive & ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(m_name);
		}

private:

	// member data
	std::string m_name;

private:

	// signals
	boost::signal<void ()> m_signal_name_change;

};

} // namespace mojo

#endif // MOJO_AUDIO_TRACK_INCLUDED
