
#define BOOST_TEST_MODULE mojo_audiofile_modules

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <boost/format.hpp>

#include <mojo/app.hpp>
#include <mojo/audio_file.hpp>
#include <mojo/audio_file_format.hpp>
#include <mojo/audio_file_module.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

#define fmt boost::format

void
test_audiofile_format (AudioFileFormatSPtr format)
{
	BOOST_REQUIRE(format);

	BOOST_TEST_MESSAGE(format->name());
	BOOST_TEST_MESSAGE(format->extension());
}

void
test_read_audiofile (AudioFileSPtr af)
{
	const unsigned int frame_count = 4096U;
	const unsigned int buffer_size = frame_count * af->channels();

	BOOST_TEST_MESSAGE(fmt("Using buffer size: %1% ") % buffer_size);

	float* buffer = new float[buffer_size];

	BOOST_REQUIRE(buffer);

	// seek to start of audio data
	BOOST_CHECK_EQUAL(af->seek(0), 0);

	count_t frames_read = 0;
	count_t total_frames = af->frames();
	
	while (frames_read < total_frames)
	{
		frames_read += af->read_frames (buffer, frame_count);

		BOOST_TEST_MESSAGE(fmt("Frames read: %1%") % frames_read);

		BOOST_CHECK_EQUAL(af->seek (frames_read), frames_read);
	}

	BOOST_CHECK_EQUAL(frames_read, total_frames);

	delete [] buffer;
}

void
test_open_existing_file (AudioFileModuleSPtr mod)
{
	AudioFileSPtr af = mod->open("share/projects/motronic/audiofiles/notify.wav");

	BOOST_REQUIRE(af);

	BOOST_CHECK_EQUAL(af->samplerate(), 22050U);
	BOOST_CHECK_EQUAL(af->channels(), 2U);
	BOOST_CHECK_EQUAL(af->frames(), 29835U);

	test_audiofile_format (af->format());

	test_read_audiofile (af);
}

void
test_formats (const AudioFileFormatSet& formats)
{
	BOOST_CHECK(!formats.empty());

	for_each (formats.begin(), formats.end(), test_audiofile_format);
}

void
test_audiofile_module (AudioFileModuleSPtr mod)
{
	BOOST_REQUIRE(mod);

	BOOST_TEST_MESSAGE(mod->get_author());
	BOOST_TEST_MESSAGE(mod->get_description());
	BOOST_TEST_MESSAGE(mod->get_version());

	test_open_existing_file (mod);

	test_formats (mod->get_readable_formats ());

	test_formats (mod->get_writable_formats ());
}

BOOST_AUTO_TEST_CASE( audiofile_module_test )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	AppSPtr app = App::init (argc, argv);
	BOOST_REQUIRE(app);

	AudioFileModuleSet modules = App::get_audiofile_modules();

	BOOST_CHECK(!modules.empty());

	for_each (modules.begin(), modules.end(), test_audiofile_module);
}