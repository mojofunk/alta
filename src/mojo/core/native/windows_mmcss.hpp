#ifndef MOJO_CORE_WINDOWS_MMCSS_H
#define MOJO_CORE_WINDOWS_MMCSS_H

namespace mmcss {

enum AVRT_PRIORITY {
	AVRT_PRIORITY_VERYLOW = -2,
	AVRT_PRIORITY_LOW,
	AVRT_PRIORITY_NORMAL,
	AVRT_PRIORITY_HIGH,
	AVRT_PRIORITY_CRITICAL
};

enum error_codes {
	ERROR_INVALID_TASK_NAME = 1550,
	ERROR_INVALID_TASK_INDEX = 1551
};

bool initialize();

bool deinitialize();

bool set_thread_characteristics(const std::string& task_name,
                                void** task_handle);

bool revert_thread_characteristics(void* task_handle);

bool set_thread_priority(void*, AVRT_PRIORITY);

} // namespace mmcss

#endif // MOJO_CORE_WINDOWS_MMCSS_H
