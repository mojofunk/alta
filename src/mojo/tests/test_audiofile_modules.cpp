#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_audiofile_modules
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include "mojo/core/string/compose.hpp"

#include "mojo/audio_file/audio_file.hpp"
#include "mojo/audio_file/audio_file_format.hpp"
#include "mojo/audio_file/audio_file_module.hpp"

#include "mojo/application/application.hpp"
#include "mojo/application/project_directory.hpp"

#include "test_common.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

void test_audiofile_format(AudioFileFormatSP format)
{
	BOOST_REQUIRE(format);

	BOOST_TEST_MESSAGE(format->name());
	BOOST_TEST_MESSAGE(format->extension());
}

void test_read_audiofile(AudioFileSP af)
{
	const unsigned int frame_count = 4096U;
	const unsigned int buffer_size = frame_count * af->channels();

	BOOST_TEST_MESSAGE(compose("Using buffer size: %", buffer_size));

	float* buffer = new float[buffer_size];

	BOOST_REQUIRE(buffer);

	// seek to start of audio data
	BOOST_CHECK_EQUAL(af->seek(0), 0);

	count_t frames_read = 0;
	count_t total_frames = af->frames();

	while (frames_read < total_frames) {
		frames_read += af->read_frames(buffer, frame_count);

		BOOST_TEST_MESSAGE(compose("Frames read: %", frames_read));

		BOOST_CHECK_EQUAL(af->seek(frames_read), frames_read);
	}

	BOOST_CHECK_EQUAL(frames_read, total_frames);

	delete[] buffer;
}

void test_open_existing_file(AudioFileModuleSP mod)
{
	fs::path project_path;

	BOOST_CHECK(find_directory_in_test_path("projects", project_path));

	project_path = project_path / "motronic";

	BOOST_TEST_MESSAGE(compose("project_path: %", project_path));

	BOOST_CHECK(fs::exists(project_path));

	fs::path audiofile_path =
	    ProjectDirectory(project_path).audiofiles_path() / "notify.wav";

	BOOST_CHECK(fs::exists(audiofile_path));

	AudioFileSP af = mod->open(audiofile_path.string());

	BOOST_REQUIRE(af);

	BOOST_CHECK_EQUAL(af->samplerate(), 22050U);
	BOOST_CHECK_EQUAL(af->channels(), 2U);
	BOOST_CHECK_EQUAL(af->frames(), 29835U);

	test_audiofile_format(af->format());

	test_read_audiofile(af);
}

void test_formats(const AudioFileFormatSPSet& formats)
{
	BOOST_CHECK(!formats.empty());

	for_each(formats.begin(), formats.end(), test_audiofile_format);
}

void test_audiofile_module(AudioFileModuleSP mod)
{
	BOOST_REQUIRE(mod);

	BOOST_TEST_MESSAGE(mod->get_author());
	BOOST_TEST_MESSAGE(mod->get_description());
	BOOST_TEST_MESSAGE(mod->get_version());

	test_open_existing_file(mod);

	test_formats(mod->get_readable_formats());

	test_formats(mod->get_writable_formats());
}

BOOST_AUTO_TEST_CASE(audiofile_module_test)
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	Application::initialize();
	AudioFileModuleSPSet modules = Application::get_audiofile_modules();

	BOOST_CHECK(!modules.empty());

	for_each(modules.begin(), modules.end(), test_audiofile_module);
	Application::deinitialize();
}
