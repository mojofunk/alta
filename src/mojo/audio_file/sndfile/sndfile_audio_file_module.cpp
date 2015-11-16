namespace mojo {

SndfileAudioFileModule::SndfileAudioFileModule()
{
	get_readable_formats(m_readable_formats);
	get_writable_formats(m_writable_formats);
}

SndfileAudioFileModule::~SndfileAudioFileModule()
{
}

void SndfileAudioFileModule::get_readable_formats(AudioFileFormatSPSet& formats)
{
	SF_FORMAT_INFO info;
	SF_INFO sfinfo;
	int major_count, subtype_count;

	memset(&sfinfo, 0, sizeof(sfinfo));

	sf_command(NULL, SFC_GET_FORMAT_MAJOR_COUNT, &major_count, sizeof(int));
	sf_command(NULL, SFC_GET_FORMAT_SUBTYPE_COUNT, &subtype_count, sizeof(int));

	sfinfo.channels = 1;

	for (int m = 0; m < major_count; ++m) {
		info.format = m;
		sf_command(NULL, SFC_GET_FORMAT_MAJOR, &info, sizeof(info));

		int major_format = info.format;

		for (int s = 0; s < subtype_count; ++s) {
			info.format = s;
			sf_command(NULL, SFC_GET_FORMAT_SUBTYPE, &info, sizeof(info));

			sfinfo.format = (major_format & SF_FORMAT_TYPEMASK) | info.format;

			if (sf_format_check(&sfinfo)) {
				AudioFileFormatSP f(new SndfileAudioFileFormat(sfinfo.format));
				formats.insert(f);
			}
		}
	}
}

void SndfileAudioFileModule::get_writable_formats(AudioFileFormatSPSet& formats)
{
	formats.insert(AudioFileFormatSP(
	    new SndfileAudioFileFormat(SF_FORMAT_WAV | SF_FORMAT_FLOAT)));
}

std::string SndfileAudioFileModule::get_author()
{
	return "Tim Mayberry";
}

std::string SndfileAudioFileModule::get_description()
{
	return "libsndfile module";
}

std::string SndfileAudioFileModule::get_version()
{
	return "0.0.1";
}

AudioFileSP SndfileAudioFileModule::open(const std::string& path)
{
	AudioFileSP audio_file;

	try {
		audio_file = AudioFileSP(new SndfileAudioFile(path));
	}
	catch (const SndfileException& e) {
		std::cerr << e.what() << std::endl;
	}
	return audio_file;
}

AudioFileSP SndfileAudioFileModule::open(const std::string& path,
                                         AudioFileFormatSP format,
                                         samplerate_t rate,
                                         channel_count_t channels)
{
	return AudioFileSP();
}

AudioFileFormatSPSet SndfileAudioFileModule::get_readable_formats() const
{
	return m_readable_formats;
}

AudioFileFormatSPSet SndfileAudioFileModule::get_writable_formats() const
{
	return m_writable_formats;
}

MOJO_CAPI void* mojo_module_factory(void)
{
	return new SndfileAudioFileModule;
}

} // namespace mojo
