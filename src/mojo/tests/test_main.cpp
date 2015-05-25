#ifdef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_tests
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/framework.hpp>

#ifdef MOJO_TEST_AMALGAMATED

#include "mojo/core/config/common_header_includes.hpp"

// common test sources
#include "example_application.cpp"
#include "test_common.cpp"

// individual tests
#include "test_application.cpp"
#include "test_archive_modules.cpp"
#include "test_audio_clip.cpp"
#include "test_audio_driver_modules.cpp"
#include "test_audio_effect_modules.cpp"
#include "test_audiofile_modules.cpp"
#include "test_core_initialize.cpp"
#include "test_debug.cpp"
#include "test_filesystem_paths.cpp"
#include "test_file_utils.cpp"
#include "test_graph.cpp"
#include "test_log.cpp"
#include "test_midi_driver_modules.cpp"
#include "test_module_utils.cpp"
#include "test_project.cpp"
#include "test_project_directory.cpp"
#include "test_resource.cpp"
#include "test_sequence.cpp"
#include "test_spinwait.cpp"
#include "test_state_tracker.cpp"
#include "test_string_compose.cpp"
#include "test_string_convert.cpp"
#include "test_timing.cpp"
#include "test_type_system.cpp"

// native tests

#ifdef MOJO_WINDOWS
#include "test_native_mmcss.cpp"
#endif

#endif
