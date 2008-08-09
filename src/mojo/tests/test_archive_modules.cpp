#define BOOST_TEST_MODULE mojo_archive_modules

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <mojo/app/app.hpp>
#include <mojo/archive.hpp>
#include <mojo/archive_module.hpp>

#include <cformat/cformat.hpp>

#include <glib.h>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

template <class T>
bool
insert_property(Properties& props, const string& name, const T& value)
{
	return props.insert(make_property<string, T>(name, value)).second;
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

void
insert_some_properties (Properties& props)
{
	BOOST_CHECK(insert_property<string>(props, "name", "timbyr"));
	BOOST_CHECK(insert_property<int32_t>(props, "age", 12));
	BOOST_CHECK(insert_property<float>(props, "avgloc", 10.53f));
}

void
check_some_properties (Properties& props)
{
	check_property<std::string>(props, "name", "timbyr");
	check_property<int32_t>(props, "age", 12);
	check_property<float>(props, "avgloc", 10.23f);
}

void
test_archive (ArchiveSPtr archive, const string& filename)
{
	Properties props;

	insert_some_properties (props);

	BOOST_CHECK_NO_THROW(archive->write (filename, props));

	props.clear();

	BOOST_CHECK_NO_THROW(archive->read (filename, props));

	check_some_properties (props);
}

BOOST_AUTO_TEST_CASE( archive_module_test )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	AppSPtr app = App::init (argc, argv);

	ArchiveModuleSet modules = App::get_archive_modules ();

	BOOST_CHECK (!modules.empty());

	for (ArchiveModuleSet::iterator i = modules.begin ();
			i != modules.end(); ++i)
	{
		string file_extension = cformat::convert<string>(g_random_int());
		string file_name = string((typeid (*i).name())) + "." + file_extension;

		ArchiveSPtr archive = (*i)->create_archive ();

		test_archive (archive, file_name);
	}
}
