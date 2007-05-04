
#ifndef MOJO_AUDIO_TRACK_INCLUDED
#define MOJO_AUDIO_TRACK_INCLUDED

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>

namespace mojo {

class AudioTrack
{
public:

	AudioTrack();

	const std::string& get_name() const;

	bool set_name(const std::string& name);

private:
	
	// serialization
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(m_name);
	}

private:

	std::string m_name;

};

} // namespace mojo

#endif
