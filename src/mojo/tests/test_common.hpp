#ifndef MOJO_TEST_COMMON_H
#define MOJO_TEST_COMMON_H

#include "mojo/core/filesystem/search_path.hpp"

mojo::Searchpath test_search_path ();

fs::path new_test_output_dir ();

#endif // MOJO_TEST_COMMON_H
