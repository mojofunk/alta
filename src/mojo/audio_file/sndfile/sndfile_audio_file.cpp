SndfileAudioFile::SndfileAudioFile(const std::string& path)
    : m_path(path)
    , m_sf(0)
{
	m_sf = sf_open(path.c_str(), SFM_RDWR, &m_info);

	if (m_sf == NULL) throw SndfileException(sf_strerror(m_sf));

	m_format = AudioFileFormatSP(new SndfileAudioFileFormat(m_info.format));
}

SndfileAudioFile::~SndfileAudioFile()
{
}

AudioFileFormatSP
SndfileAudioFile::format()
{
	return m_format;
}

count_t
SndfileAudioFile::read_frames(float* buf, count_t frame_count)
{
	return sf_readf_float(m_sf, buf, frame_count);
}

count_t
SndfileAudioFile::write_frames(float* buf, count_t frame_count)
{
	return sf_writef_float(m_sf, buf, frame_count);
}

count_t
SndfileAudioFile::seek(count_t frame_offset)
{
	return sf_seek(m_sf, frame_offset, SEEK_SET);
}

count_t
SndfileAudioFile::frames() const
{
	// read current frame offset
	sf_count_t frame_pos = sf_seek(m_sf, 0, SEEK_CUR);
	// seek to end
	sf_count_t frames = sf_seek(m_sf, 0, SEEK_END);
	// restore previous offset
	sf_seek(m_sf, frame_pos, SEEK_SET);

	return frames;
}

samplerate_t
SndfileAudioFile::samplerate() const
{
	return m_info.samplerate;
}

channel_count_t
SndfileAudioFile::channels() const
{
	return m_info.channels;
}
