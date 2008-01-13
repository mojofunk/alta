#define BOOST_TEST_MODULE mojo_dummy_archive

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <mojo/application.hpp>
#include <mojo/dummy_archive.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

template <class T>
std::pair<string, T>
create_property(const string& name, const T& value)
{
	
	return make_property<string, T>(name, value);
	
}

template <class T>
void
check_property (const Properties& props, const string& property_name, const T& expected_value)
{
	Properties::const_iterator i;
	BOOST_REQUIRE((i = props.find (property_name)) != props.end());

	T prop_value; 

	BOOST_CHECK_NO_THROW(prop_value = boost::any_cast<T>(i->second));

	BOOST_CHECK_EQUAL(prop_value, expected_value);
}

BOOST_AUTO_TEST_CASE( dummy_archive_test )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	ApplicationSPtr app = Application::create (argc, argv);

	DummyArchive archive;
	Properties props;

	BOOST_CHECK(props.insert (create_property<string>("name", "timbyr")).second);
	BOOST_CHECK(props.insert (create_property<int32_t>("age", 12)).second);
	BOOST_CHECK(props.insert (create_property<float>("avgloc", 10.23f)).second);

	BOOST_CHECK_NO_THROW(archive.write ("dummy", props));

	props.clear();

	BOOST_CHECK_NO_THROW(archive.read ("dummy", props));

	check_property<std::string>(props, "name", "timbyr");
	check_property<int32_t>(props, "age", 12);
	check_property<float>(props, "avgloc", 10.23f);
}
