
#include "sndfile_audio_file_plugin.hpp"
#include "sndfile_audio_file.hpp"
#include "sndfile_audio_file_format.hpp"

#include <mojo/export.h>

#include <iostream>
using namespace std;

namespace mojo {

SndfileAudioFilePlugin::SndfileAudioFilePlugin ()
{
	get_readable_formats (m_readable_formats);

}

SndfileAudioFilePlugin::~SndfileAudioFilePlugin ()
{
	delete_formats (m_readable_formats);
}

void
SndfileAudioFilePlugin::get_readable_formats (Formats& formats)
{
	SF_FORMAT_INFO          info;
	SF_INFO                 sfinfo ;
	int major_count, subtype_count;

	memset (&sfinfo, 0, sizeof (sfinfo)) ;

	sf_command (NULL, SFC_GET_FORMAT_MAJOR_COUNT, &major_count, sizeof (int)) ;
	sf_command (NULL, SFC_GET_FORMAT_SUBTYPE_COUNT, &subtype_count, sizeof (int)) ;

	sfinfo.channels = 1;

	for (int m = 0 ; m < major_count ; ++m)
	{
		info.format = m;
		sf_command (NULL, SFC_GET_FORMAT_MAJOR, &info, sizeof (info));

		int major_format = info.format ;

		for (int s = 0 ; s < subtype_count ; ++s)
		{
			info.format = s ;
			sf_command (NULL, SFC_GET_FORMAT_SUBTYPE, &info, sizeof (info)) ;

			sfinfo.format = (major_format & SF_FORMAT_TYPEMASK) | info.format;

			if (sf_format_check (&sfinfo))
			{
				SndfileAudioFileFormat* f = new SndfileAudioFileFormat(sfinfo.format);
				formats.push_back (f);
			}
		}
	}
}

static void
delete_format (AudioFileFormat* f) { delete f; }

void
SndfileAudioFilePlugin::delete_formats (AudioFilePlugin::Formats& formats)
{
	for_each (formats.begin(), formats.end(), delete_format);
	formats.clear();
}

std::string
SndfileAudioFilePlugin::get_author()
{
	return "Tim Mayberry";
}

std::string
SndfileAudioFilePlugin::get_description()
{
	return "libsndfile plugin";
}

std::string
SndfileAudioFilePlugin::get_version()
{
	return "0.0.1";
}

AudioFile*
SndfileAudioFilePlugin::open (const std::string& path)
{
	SndfileAudioFile* audio_file = 0;

	try
	{
		audio_file = new SndfileAudioFile(path);
	}
	catch(const SndfileException& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return audio_file;
}

AudioFilePlugin::Formats
SndfileAudioFilePlugin::get_readable_formats () const
{
	return m_readable_formats;
}

MOJO_CAPI void * mojo_plugin_factory(void)
{
	return new SndfileAudioFilePlugin;
}

} // namespace mojo
