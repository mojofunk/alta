
#ifndef UI_PROJECT
#define UI_PROJECT

#include <sigc++/trackable.h>
#include <sigc++/signal.h>

namespace ui {

class Track;
class ProjectData;

class Project : public sigc::trackable
{
public: // typedefs

	typedef sigc::signal<void, Track*> track_signal_t;
	typedef sigc::signal<void> transport_changed_signal_t;

public: // constructors

	Project ();

	~Project ();

public: // methods

	void save ();

	void create_audio_track ();

	void set_playing (bool);
	bool get_playing ();

	void set_looping (bool);
	bool get_looping ();

public: // signal accessors

	track_signal_t& signal_track_added ()
	{ return m_signal_track_added; }

	track_signal_t& signal_track_removed ()
	{ return m_signal_track_removed; }

	transport_changed_signal_t& transport_changed_signal ()
	{ return m_signal_transport_changed; }

private: // signals

	track_signal_t m_signal_track_added;
	track_signal_t m_signal_track_removed;

	transport_changed_signal_t m_signal_transport_changed;

private: // data

	ProjectData* m_data;

};

} // namespace ui

#endif
