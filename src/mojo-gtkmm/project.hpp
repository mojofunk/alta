
#ifndef UI_PROJECT_INCLUDED
#define UI_PROJECT_INCLUDED

#include <sigc++/trackable.h>
#include <sigc++/signal.h>

namespace ui {

class Track;
class ProjectData;

class Project : public sigc::trackable
{
public: // typedefs

	typedef sigc::signal<void, Track*> track_signal_t;

public: // constructors

	Project ();

public: // methods

	void save ();

	void create_audio_track ();

public: // signal accessors

	track_signal_t& track_added_signal ()
	{ return m_signal_track_added; }

private: // signals

	track_signal_t m_signal_track_added;

private: // data

	ProjectData* m_data;

};

} // namespace ui

#endif
