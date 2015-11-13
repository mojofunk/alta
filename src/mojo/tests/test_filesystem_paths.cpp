#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_filesystem_paths
#endif

#include "test_includes.hpp"

void log_paths(const paths_t& paths)
{
	for (auto const& i : paths) {
		BOOST_TEST_MESSAGE(i);
	}
}

BOOST_AUTO_TEST_CASE(test_user_config_dir)
{
	const fs::path user_config_dir = get_user_config_directory();

	BOOST_CHECK(!user_config_dir.empty());

	BOOST_TEST_MESSAGE(user_config_dir);
}

BOOST_AUTO_TEST_CASE(test_user_data_dir)
{
	const fs::path user_data_dir = get_user_data_directory();

	BOOST_CHECK(!user_data_dir.empty());

	BOOST_TEST_MESSAGE(user_data_dir);
}

BOOST_AUTO_TEST_CASE(test_data_search_path)
{
	paths_t data_paths = get_system_data_directories();

	BOOST_CHECK(!data_paths.empty());

	log_paths(data_paths);
}

BOOST_AUTO_TEST_CASE(test_config_search_path)
{
	paths_t config_paths = get_system_config_directories();

	BOOST_CHECK(!config_paths.empty());

	log_paths(config_paths);
}

void test_path(const fs::path& p)
{
	BOOST_REQUIRE(!p.empty());
	BOOST_TEST_MESSAGE(p);
}

void test_search_path(const Searchpath& sp)
{
	for_each(sp.begin(), sp.end(), test_path);
}

BOOST_AUTO_TEST_CASE(user_config_dir_test)
{
	test_path(user_config_directory());
}

BOOST_AUTO_TEST_CASE(mojo_search_path_test)
{
	test_search_path(mojo_search_path());
}

BOOST_AUTO_TEST_CASE(system_config_search_path_test)
{
	test_search_path(system_config_search_path());
}

BOOST_AUTO_TEST_CASE(system_data_search_path_test)
{
	test_search_path(system_data_search_path());
}

BOOST_AUTO_TEST_CASE(module_search_path_test)
{
	test_search_path(module_search_path());
}
