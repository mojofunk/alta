#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_project_directory
#endif

#include "test_includes.hpp"

#include "mojo-application.hpp"

BOOST_AUTO_TEST_CASE(test_project_directory)
{
	BOOST_CHECK(fs::exists(test_search_path().get_paths().front()));

	fs::path project_path = test_search_path().get_paths().front();

	project_path = project_path / "projects" / "motronic";

	ProjectDirectory pdir(project_path);

	bool is_new = false;

	BOOST_CHECK_NO_THROW(is_new = pdir.create());

	BOOST_CHECK(!is_new);

	BOOST_CHECK(is_directory(pdir.root_path()));
	BOOST_CHECK(is_directory(pdir.audiofiles_path()));
	BOOST_CHECK(is_directory(pdir.peak_path()));

	BOOST_CHECK(pdir.is_valid());
}
