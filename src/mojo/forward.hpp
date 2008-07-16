
#ifndef MOJO_FORWARD_INCLUDED
#define MOJO_FORWARD_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class App;

	typedef boost::shared_ptr<App>    AppSPtr;
	typedef boost::weak_ptr<App>      AppWPtr;

	class Archive;

	typedef boost::shared_ptr<Archive>    ArchiveSPtr;
	typedef boost::weak_ptr<Archive>      ArchiveWPtr;

	class AudioClip;

	typedef boost::shared_ptr<AudioClip>    AudioClipSPtr;
	typedef boost::weak_ptr<AudioClip>      AudioClipWPtr;

	class AudioDriverModule;

	typedef boost::shared_ptr<AudioDriverModule>    AudioDriverModuleSPtr;
	typedef boost::weak_ptr<AudioDriverModule>      AudioDriverModuleWPtr;

	class AudioEffectModule;

	typedef boost::shared_ptr<AudioEffectModule>    AudioEffectModuleSPtr;
	typedef boost::weak_ptr<AudioEffectModule>      AudioEffectModuleWPtr;

	class AudioEvent;

	typedef boost::shared_ptr<AudioEvent>    AudioEventSPtr;
	typedef boost::weak_ptr<AudioEvent>      AudioEventWPtr;

	class AudioFileModule;

	typedef boost::shared_ptr<AudioFileModule>    AudioFileModuleSPtr;
	typedef boost::weak_ptr<AudioFileModule>      AudioFileModuleWPtr;

	class AudioFile;

	typedef boost::shared_ptr<AudioFile>    AudioFileSPtr;
	typedef boost::weak_ptr<AudioFile>      AudioFileWPtr;

	class AudioRegion;

	typedef boost::shared_ptr<AudioRegion>    AudioRegionSPtr;
	typedef boost::weak_ptr<AudioRegion>      AudioRegionWPtr;

	class AudioSequence;

	typedef boost::shared_ptr<AudioSequence>    AudioSequenceSPtr;
	typedef boost::weak_ptr<AudioSequence>      AudioSequenceWPtr;

	class AudioTrack;

	typedef boost::shared_ptr<AudioTrack>    AudioTrackSPtr;
	typedef boost::weak_ptr<AudioTrack>      AudioTrackWPtr;

	class MidiTrack;

	typedef boost::shared_ptr<MidiTrack>    MidiTrackSPtr;
	typedef boost::weak_ptr<MidiTrack>      MidiTrackWPtr;

	class Object;

	typedef boost::shared_ptr<Object>    ObjectSPtr;
	typedef boost::weak_ptr<Object>      ObjectWPtr;
	
	class Module;

	typedef boost::shared_ptr<Module>    ModuleSPtr;
	typedef boost::weak_ptr<Module>      ModuleWPtr;

	class Project;

	typedef boost::shared_ptr<Project>    ProjectSPtr;
	typedef boost::weak_ptr<Project>      ProjectWPtr;

	class Track;

	typedef boost::shared_ptr<Track>    TrackSPtr;
	typedef boost::weak_ptr<Track>      TrackWPtr;

	class TypeFactory;

	typedef boost::shared_ptr<TypeFactory>    TypeFactorySPtr;
	typedef boost::weak_ptr<TypeFactory>      TypeFactoryWPtr;

	class TypeSystem;

	typedef boost::shared_ptr<TypeSystem>    TypeSystemSPtr;
	typedef boost::weak_ptr<TypeSystem>      TypeSystemWPtr;

} // namespace mojo

#endif
