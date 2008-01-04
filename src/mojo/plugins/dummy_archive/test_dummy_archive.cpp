#define BOOST_TEST_MODULE mojo_dummy_archive

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <mojo/plugins/dummy_archive/dummy_archive.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

template <class T>
void
test_type(DummyArchive& archive, const string& name, const T& value)
{
	// add property to archive
	archive.set_property(name, value);

	boost::any any_value;

	// check that it was added properly 
	archive.get_property(name, any_value);

	BOOST_CHECK(!any_value.empty());
	
	BOOST_CHECK(any_value.type() == typeid(T));

	T same_value = boost::any_cast<T>(any_value);

	BOOST_CHECK_EQUAL(value, same_value);
}

BOOST_AUTO_TEST_CASE( dummy_archive_test )
{
	DummyArchive archive;

	test_type<string>(archive, "string", "test-string");
	test_type<int>(archive, "int", 123);
	test_type<float>(archive, "float", 1.23f);
}
