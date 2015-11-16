namespace mojo {

SndfileAudioFileFormat::SndfileAudioFileFormat(int sndfile_format)
    : m_format(sndfile_format)
{
}

string SndfileAudioFileFormat::name() const
{
	SF_FORMAT_INFO info;

	info.format = m_format & SF_FORMAT_TYPEMASK;

	sf_command(NULL, SFC_GET_FORMAT_INFO, &info, sizeof(info));

	const string major_format_name = info.name;

	info.format = m_format & SF_FORMAT_SUBMASK;

	sf_command(NULL, SFC_GET_FORMAT_INFO, &info, sizeof(info));

	const string minor_format_name = info.name;

	return major_format_name + ", " + minor_format_name;
}

string SndfileAudioFileFormat::extension() const
{
	SF_FORMAT_INFO info;

	info.format = m_format & SF_FORMAT_TYPEMASK;

	sf_command(NULL, SFC_GET_FORMAT_INFO, &info, sizeof(info));

	return string(".") + info.extension;
}

int SndfileAudioFileFormat::format() const
{
	return m_format;
}

} // namespace mojo
