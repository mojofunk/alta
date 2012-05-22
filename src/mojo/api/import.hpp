
#ifndef MOJO_IMPORT
#define MOJO_IMPORT

namespace mojo {


/**
 * task_t is an identifier for a particular task
 *
 * The task_t can be used to discover the status of task,
 * cancel a task etc.
 *
 * import options:
 *
 * copy files to audio folder
 * split multi-channel files into mono files
 *
 * The files are added to the project that is active for the application
 *
 */
task_t
Application::import_audiofiles (const paths& files, const ImportOptions&)
{


}

#endif
