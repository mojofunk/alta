
#ifndef GMOJO_NEW_AUDIO_TRACK_DIALOG_INCLUDED
#define GMOJO_NEW_AUDIO_TRACK_DIALOG_INCLUDED

#include <boost/noncopyable.hpp>

namespace gmojo {

class NewAudioTrackDialog : public boost::noncopyable
{
public:

	enum Response {
		Cancel,
		New
	};

	NewAudioTrackDialog();

	Response run ();

private:

};

} // namespace gmojo

#endif
