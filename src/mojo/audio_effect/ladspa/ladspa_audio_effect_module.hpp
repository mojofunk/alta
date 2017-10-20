#ifndef MOJO_LADSPA_AUDIO_EFFECT_MODULE_H
#define MOJO_LADSPA_AUDIO_EFFECT_MODULE_H

class LADSPAAudioEffectModule : public AudioEffectModule
{
public: // constructors
	LADSPAAudioEffectModule();

	~LADSPAAudioEffectModule();

public: // Module interface
	virtual std::string get_author();

	virtual std::string get_description();

	virtual std::string get_version();

public: // AudioEffectModule interface
	virtual AudioEffectSP open(AudioEffectInfoSP info, samplerate_t rate);

	virtual paths_t get_plugin_directory_paths() const;

	virtual void set_plugin_directory_paths(const paths_t& paths);

	virtual paths_t get_preset_directory_paths() const;

	virtual void set_preset_directory_paths(const paths_t& paths);

	virtual AudioEffectInfoSPSet get_plugin_info();

	virtual std::string get_plugin_api_name() const;

private:
	void get_info(const fs::path& path, AudioEffectInfoSPSet& info_set);

	paths_t m_plugin_dirs;
};

#endif // MOJO_LADSPA_AUDIO_EFFECT_MODULE_H
