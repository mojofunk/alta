MOJO_DEBUG_DOMAIN(WINDOWS_MMCSS)

typedef HANDLE(WINAPI* AvSetMmThreadCharacteristicsA_t)(LPCSTR TaskName,
                                                        LPDWORD TaskIndex);

typedef WINBOOL(WINAPI* AvRevertMmThreadCharacteristics_t)(HANDLE AvrtHandle);

typedef WINBOOL(WINAPI* AvSetMmThreadPriority_t)(
    HANDLE AvrtHandle, mojo::mmcss::AVRT_PRIORITY Priority);

static HMODULE avrt_dll = NULL;

static AvSetMmThreadCharacteristicsA_t AvSetMmThreadCharacteristicsA = NULL;
static AvRevertMmThreadCharacteristics_t AvRevertMmThreadCharacteristics = NULL;
static AvSetMmThreadPriority_t AvSetMmThreadPriority = NULL;

namespace mmcss {

bool initialize()
{
	if (avrt_dll != NULL) return true;

	avrt_dll = LoadLibraryA("avrt.dll");

	if (avrt_dll == NULL) {
		MOJO_DEBUG_MSG(WINDOWS_MMCSS, "Unable to load avrt.dll");
		return false;
	}
	bool unload_dll = false;

	AvSetMmThreadCharacteristicsA =
	    (AvSetMmThreadCharacteristicsA_t)GetProcAddress(
	        avrt_dll, "AvSetMmThreadCharacteristicsA");

	if (AvSetMmThreadCharacteristicsA == NULL) {
		MOJO_DEBUG_MSG(WINDOWS_MMCSS,
		               "Unable to resolve AvSetMmThreadCharacteristicsA");
		unload_dll = true;
	}

	AvRevertMmThreadCharacteristics =
	    (AvRevertMmThreadCharacteristics_t)GetProcAddress(
	        avrt_dll, "AvRevertMmThreadCharacteristics");

	if (AvRevertMmThreadCharacteristics == NULL) {
		MOJO_DEBUG_MSG(WINDOWS_MMCSS,
		               "Unable to resolve AvRevertMmThreadCharacteristics");
		unload_dll = true;
	}

	AvSetMmThreadPriority =
	    (AvSetMmThreadPriority_t)GetProcAddress(avrt_dll, "AvSetMmThreadPriority");

	if (AvSetMmThreadPriority == NULL) {
		MOJO_DEBUG_MSG(WINDOWS_MMCSS, "Unable to resolve AvSetMmThreadPriority");
		unload_dll = true;
	}

	if (unload_dll) {
		MOJO_DEBUG_MSG(WINDOWS_MMCSS,
		               "Unable to resolve necessary symbols, unloading avrt.dll");
		deinitialize();
	}

	return true;
}

bool deinitialize()
{
	if (avrt_dll == NULL) return true;

	if (FreeLibrary(avrt_dll) == 0) {
		MOJO_DEBUG_MSG(WINDOWS_MMCSS, "Unable to unload avrt.dll");
		return false;
	}

	avrt_dll = NULL;

	AvSetMmThreadCharacteristicsA = NULL;
	AvRevertMmThreadCharacteristics = NULL;
	AvSetMmThreadPriority = NULL;

	return true;
}

bool set_thread_characteristics(const std::string& task_name,
                                void** task_handle)
{
	if (AvSetMmThreadCharacteristicsA == NULL) return false;

	DWORD task_index_dummy = 0;

	*task_handle =
	    AvSetMmThreadCharacteristicsA(task_name.c_str(), &task_index_dummy);

	if (*task_handle == 0) {
		MOJO_DEBUG_MSG(
		    WINDOWS_MMCSS,
		    compose("Failed to set Thread Characteristics to %", task_name));
		return false;
	}

	MOJO_DEBUG_MSG(WINDOWS_MMCSS,
	               compose("Set thread characteristics to %", task_name));

	return true;
}

bool revert_thread_characteristics(void* task_handle)
{
	if (AvRevertMmThreadCharacteristics == NULL) return false;

	if (AvRevertMmThreadCharacteristics(task_handle) == 0) {
		MOJO_DEBUG_MSG(WINDOWS_MMCSS, "Failed to set revert thread characteristics");
		return false;
	}

	MOJO_DEBUG_MSG(WINDOWS_MMCSS, "Reverted thread characteristics");

	return true;
}

bool set_thread_priority(void* task_handle, AVRT_PRIORITY priority)
{
	if (AvSetMmThreadPriority == NULL) return false;

	if (AvSetMmThreadPriority(task_handle, priority) == 0) {
		MOJO_DEBUG_MSG(WINDOWS_MMCSS,
		               compose("Failed to set thread priority %", priority));
		return false;
	}

	MOJO_DEBUG_MSG(WINDOWS_MMCSS, compose("Set thread priority to %", priority));

	return true;
}

} // namespace mmcss
