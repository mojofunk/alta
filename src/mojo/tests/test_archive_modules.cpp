#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_archive_modules
#endif

#include "test_includes.hpp"

#include "mojo-archive.hpp"
#include "mojo-application.hpp"

template <class T>
void check_property(const Properties& props,
                    const string& property_name,
                    const T& expected_value)
{
	T prop_value;

	BOOST_CHECK_NO_THROW(props.get_property(property_name, prop_value));

	BOOST_CHECK_EQUAL(prop_value, expected_value);
}

void insert_some_properties(Properties& props)
{
	props.set_property("name", string("timbyr"));
	props.set_property("age", 12);
	props.set_property("avgloc", 10.53f);
}

void check_some_properties(Properties& props)
{
	check_property<std::string>(props, "name", "timbyr");
	check_property<int32_t>(props, "age", 12);
	check_property<float>(props, "avgloc", 10.23f);
}

void test_archive(ArchiveSP archive, const string& filename)
{
	Properties props;

	insert_some_properties(props);

	BOOST_TEST_MESSAGE(filename);
	BOOST_CHECK_NO_THROW(archive->write(filename, props));

	Properties props2;

	BOOST_CHECK_NO_THROW(archive->read(filename, props2));

	// BOOST_CHECK_EQUAL (props, props2);
}

BOOST_AUTO_TEST_CASE(archive_module_test)
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	Application app;
	ArchiveModuleSPSet modules = Application::get_archive_modules();

	BOOST_CHECK(!modules.empty());

	for (auto& mod : modules) {
		string file_extension;
		BOOST_CHECK(mojo::int32_to_string(g_random_int(), file_extension));
		string file_name = string(typeid(*mod).name()) + "." + file_extension;

		BOOST_TEST_MESSAGE(mod->get_author());
		BOOST_TEST_MESSAGE(mod->get_description());
		BOOST_TEST_MESSAGE(mod->get_version());

		ArchiveSP archive = mod->create_archive();

		test_archive(archive, file_name);
	}
}
