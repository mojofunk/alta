#ifndef GLEAM_TERMINATE_PROCESS
#define GLEAM_TERMINATE_PROCESS

namespace gleam {

/**
 * Portable way of terminating the current process. This function
 * does not return.
 */
void terminate_process(int status);

} // namespace gleam

#endif // GLEAM_TERMINATE_PROCESS
