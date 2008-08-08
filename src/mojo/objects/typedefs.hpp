
#ifndef MOJO_OBJECTS_TYPEDEFS
#define MOJO_OBJECTS_TYPEDEFS

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <mojo/objects/forward.hpp>

namespace mojo {

typedef boost::shared_ptr<AudioClip>    AudioClipSPtr;
typedef boost::weak_ptr<AudioClip>      AudioClipWPtr;

typedef boost::shared_ptr<AudioEvent>    AudioEventSPtr;
typedef boost::weak_ptr<AudioEvent>      AudioEventWPtr;

typedef boost::shared_ptr<AudioRegion>    AudioRegionSPtr;
typedef boost::weak_ptr<AudioRegion>      AudioRegionWPtr;

typedef boost::shared_ptr<AudioSequence>    AudioSequenceSPtr;
typedef boost::weak_ptr<AudioSequence>      AudioSequenceWPtr;

typedef boost::shared_ptr<AudioTrack>    AudioTrackSPtr;
typedef boost::weak_ptr<AudioTrack>      AudioTrackWPtr;

typedef boost::shared_ptr<MidiTrack>    MidiTrackSPtr;
typedef boost::weak_ptr<MidiTrack>      MidiTrackWPtr;

typedef boost::shared_ptr<Object>    ObjectSPtr;
typedef boost::weak_ptr<Object>      ObjectWPtr;

typedef boost::shared_ptr<Project>    ProjectSPtr;
typedef boost::weak_ptr<Project>      ProjectWPtr;
	
typedef boost::shared_ptr<Track>    TrackSPtr;
typedef boost::weak_ptr<Track>      TrackWPtr;

} // namespace mojo

#endif
