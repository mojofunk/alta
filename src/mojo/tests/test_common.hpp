#ifndef MOJO_TEST_COMMON_H
#define MOJO_TEST_COMMON_H

#include "mojo-core.hpp"

using namespace mojo;

mojo::Searchpath
test_search_path();

bool
find_file_in_test_path(const std::string& filename, fs::path& result);

bool
find_directory_in_test_path(const std::string& directory, fs::path& result);

#endif // MOJO_TEST_COMMON_H
