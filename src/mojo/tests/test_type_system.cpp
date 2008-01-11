
#define BOOST_TEST_MODULE mojo_type_system

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <mojo/application.hpp>
#include <mojo/audio_track.hpp>
#include <mojo/audio_track_ptr.hpp>

#include <mojo/type_system.hpp>
#include <mojo/type_names.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

template <class T>
bool
test_type_name (const string& type_name)
{
	return (TypeSystem::get_type_name (typeid(T)) == type_name);
}

template <class T>
void
test_type_factory (const string& type_name)
{
	T* instance = boost::any_cast<T*>(TypeSystem::create_type(type_name));

	BOOST_REQUIRE(instance);

	delete instance;
}

BOOST_AUTO_TEST_CASE( mojo_test_type_system )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	ApplicationSPtr app = Application::create (argc, argv);

	BOOST_CHECK(test_type_name<int>(int_type_name));
	BOOST_CHECK(test_type_name<float>(float_type_name));
	BOOST_CHECK(test_type_name<string>(string_type_name));
	BOOST_CHECK(test_type_name<AudioTrack>(audio_track_type_name));

	BOOST_CHECK_NO_THROW(test_type_factory<int>(int_type_name));
	BOOST_CHECK_NO_THROW(test_type_factory<float>(float_type_name));
	BOOST_CHECK_NO_THROW(test_type_factory<string>(string_type_name));
	BOOST_CHECK_NO_THROW(test_type_factory<AudioTrack>(audio_track_type_name));
}
