
#ifndef MOJO_TYPEDEFS
#define MOJO_TYPEDEFS

#include <set>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <mojo/forward.hpp>

namespace mojo {

typedef boost::shared_ptr<App>    AppSPtr;
typedef boost::weak_ptr<App>      AppWPtr;

typedef boost::shared_ptr<Archive>    ArchiveSPtr;
typedef boost::weak_ptr<Archive>      ArchiveWPtr;

typedef boost::shared_ptr<ArchiveModule>    ArchiveModuleSPtr;
typedef boost::weak_ptr<ArchiveModule>      ArchiveModuleWPtr;

typedef boost::shared_ptr<AudioClip>    AudioClipSPtr;
typedef boost::weak_ptr<AudioClip>      AudioClipWPtr;

typedef boost::shared_ptr<AudioDriverModule>    AudioDriverModuleSPtr;
typedef boost::weak_ptr<AudioDriverModule>      AudioDriverModuleWPtr;

typedef boost::shared_ptr<AudioEffectModule>    AudioEffectModuleSPtr;
typedef boost::weak_ptr<AudioEffectModule>      AudioEffectModuleWPtr;

typedef boost::shared_ptr<AudioEvent>    AudioEventSPtr;
typedef boost::weak_ptr<AudioEvent>      AudioEventWPtr;

typedef boost::shared_ptr<AudioFileModule>    AudioFileModuleSPtr;
typedef boost::weak_ptr<AudioFileModule>      AudioFileModuleWPtr;

typedef boost::shared_ptr<AudioFile>    AudioFileSPtr;
typedef boost::weak_ptr<AudioFile>      AudioFileWPtr;

typedef boost::shared_ptr<AudioRegion>    AudioRegionSPtr;
typedef boost::weak_ptr<AudioRegion>      AudioRegionWPtr;

typedef boost::shared_ptr<AudioSequence>    AudioSequenceSPtr;
typedef boost::weak_ptr<AudioSequence>      AudioSequenceWPtr;

typedef boost::shared_ptr<AudioTrack>    AudioTrackSPtr;
typedef boost::weak_ptr<AudioTrack>      AudioTrackWPtr;

typedef boost::shared_ptr<MidiTrack>    MidiTrackSPtr;
typedef boost::weak_ptr<MidiTrack>      MidiTrackWPtr;

typedef boost::shared_ptr<Module>    ModuleSPtr;
typedef boost::weak_ptr<Module>      ModuleWPtr;

typedef boost::shared_ptr<Object>    ObjectSPtr;
typedef boost::weak_ptr<Object>      ObjectWPtr;

typedef boost::shared_ptr<Project>    ProjectSPtr;
typedef boost::weak_ptr<Project>      ProjectWPtr;
	
typedef boost::shared_ptr<Track>    TrackSPtr;
typedef boost::weak_ptr<Track>      TrackWPtr;

typedef boost::shared_ptr<TypeFactory>    TypeFactorySPtr;
typedef boost::weak_ptr<TypeFactory>      TypeFactoryWPtr; 

typedef boost::shared_ptr<TypeSystem>    TypeSystemSPtr;
typedef boost::weak_ptr<TypeSystem>      TypeSystemWPtr;

typedef std::set<ArchiveModuleSPtr>         ArchiveModuleSet;
typedef std::set<AudioDriverModuleSPtr>     AudioDriverModuleSet;
typedef std::set<AudioEffectModuleSPtr>     AudioEffectModuleSet;
typedef std::set<AudioFileModuleSPtr>       AudioFileModuleSet;
typedef std::set<ModuleSPtr>                ModuleSet;

typedef std::set<AudioDevice*>              AudioDeviceSet;

} // namespace mojo




#endif
