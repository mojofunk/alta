#ifndef MOJO_CORE_WINDOWS_MMCSS_H
#define MOJO_CORE_WINDOWS_MMCSS_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#endif

namespace mojo {

namespace mmcss {

enum AVRT_PRIORITY {
	AVRT_PRIORITY_VERYLOW = -2,
	AVRT_PRIORITY_LOW,
	AVRT_PRIORITY_NORMAL,
	AVRT_PRIORITY_HIGH,
	AVRT_PRIORITY_CRITICAL
};

bool initialize();

bool deinitialize();

bool set_thread_characteristics(const std::string& task_name,
                                void** task_handle);

bool revert_thread_characteristics(void* task_handle);

bool set_thread_priority(void*, AVRT_PRIORITY);

} // namespace mmcss

} // namespace mojo

#endif // MOJO_CORE_WINDOWS_MMCSS_H
