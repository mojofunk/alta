#ifndef MOJO_PROJECT_H
#define MOJO_PROJECT_H

namespace mojo {

/**
 * The bus names that represent physical inputs and outputs won't change when
 * the project moves between systems with different hardware devices. The names
 * associated with the hardware devices will change but they should be stored
 * with the project so that for the common case where the project being
 * reloaded on the system that it was last configured/used on all the
 * connections will be automatic.
 *
 * The Project class contains the tracks and other data needed to reconstruct a
 * project. The additional methods to get/set_properties should be for
 * convenience.
 *
 * The Project class is not tied to any on disk format
 *
 * Project contains all the data for a project, that includes project history
 *
 * The State of each Object in the project must be monitored by the
 * StateTracker so the history can be preserved and so Project can be marked as
 * "dirty" and needing to be saved.
 *
 * If all Objects in a project can only be in one project then perhaps instead
 * of using signals to tell the Project(the only listener) that the state has
 * changed or that the class is being destroyed each Object has
 * PropertyListener interface or something
 *
 *
 */
class Project : Object {
public: // Object interface
	virtual void get_properties(Properties& props) const;

	virtual void set_properties(const Properties& props);

public: // convenience methods
	AudioTrackSP new_audio_track(const std::string& name = "");

	MidiTrackSP new_midi_track(const std::string& name = "");

	TrackSPSet get_tracks() const { return m_tracks; }

	void add_track(const TrackSP&);

	void remove_track(const TrackSP&);

public: // signals
	using TrackAddedASyncSignal = signals::signal<void(Track*)>;
	using TrackRemovedSyncSignal = signals::signal<void(Track*)>;
	using TrackAddedFunc = TrackAddedASyncSignal::slot_type;
	using TrackRemovedFunc = TrackRemovedSyncSignal::slot_type;

	signals::connection connect_track_added(const TrackAddedFunc& slot);

	signals::connection connect_track_removed(const TrackRemovedFunc& slot);

private: // signal members
	TrackAddedASyncSignal m_track_added;
	TrackRemovedSyncSignal m_track_removed;

private: // member data
	std::string m_name;
	TrackSPSet m_tracks;

private: // property names
	static const char* const s_property_tracks;
};

} // namespace mojo

#endif // MOJO_PROJECT_H
