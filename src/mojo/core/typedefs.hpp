
#ifndef MOJO_TYPEDEFS
#define MOJO_TYPEDEFS

#include <set>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "forward.hpp"

namespace mojo {

typedef boost::shared_ptr<Archive>    ArchiveSPtr;
typedef boost::weak_ptr<Archive>      ArchiveWPtr;

typedef boost::shared_ptr<ArchiveModule>    ArchiveModuleSPtr;
typedef boost::weak_ptr<ArchiveModule>      ArchiveModuleWPtr;

typedef boost::shared_ptr<AudioDevice>    AudioDeviceSPtr;
typedef boost::weak_ptr<AudioDevice>      AudioDeviceWPtr;

typedef boost::shared_ptr<AudioDriverModule>    AudioDriverModuleSPtr;
typedef boost::weak_ptr<AudioDriverModule>      AudioDriverModuleWPtr;

typedef boost::shared_ptr<AudioEffect>    AudioEffectSPtr;
typedef boost::weak_ptr<AudioEffect>      AudioEffectWPtr;

typedef boost::shared_ptr<AudioEffectInfo>    AudioEffectInfoSPtr;
typedef boost::weak_ptr<AudioEffectInfo>      AudioEffectInfoWPtr;

typedef boost::shared_ptr<AudioEffectModule>    AudioEffectModuleSPtr;
typedef boost::weak_ptr<AudioEffectModule>      AudioEffectModuleWPtr;

typedef boost::shared_ptr<AudioEffectParameterInfo>    AudioEffectParameterInfoSPtr;
typedef boost::weak_ptr<AudioEffectParameterInfo>      AudioEffectParameterInfoWPtr;

typedef boost::shared_ptr<AudioFileModule>    AudioFileModuleSPtr;
typedef boost::weak_ptr<AudioFileModule>      AudioFileModuleWPtr;

typedef boost::shared_ptr<AudioFile>    AudioFileSPtr;
typedef boost::weak_ptr<AudioFile>      AudioFileWPtr;

typedef boost::shared_ptr<AudioFileFormat>    AudioFileFormatSPtr;
typedef boost::weak_ptr<AudioFileFormat>      AudioFileFormatWPtr;

typedef boost::shared_ptr<Module>    ModuleSPtr;
typedef boost::weak_ptr<Module>      ModuleWPtr;
	
typedef std::set<ArchiveModuleSPtr>         ArchiveModuleSet;
typedef std::set<AudioDriverModuleSPtr>     AudioDriverModuleSet;
typedef std::set<AudioEffectModuleSPtr>     AudioEffectModuleSet;
typedef std::set<AudioFileModuleSPtr>       AudioFileModuleSet;
typedef std::set<ModuleSPtr>                ModuleSet;

typedef std::set<AudioDeviceSPtr>           AudioDeviceSet;

typedef std::set<AudioFileFormatSPtr>       AudioFileFormatSet;

typedef std::set<AudioEffectInfoSPtr>       AudioEffectInfoSet;

} // namespace mojo

#endif
