#ifndef MOJO_CORE_CORE_INITIALIZE_H
#define MOJO_CORE_CORE_INITIALIZE_H

namespace core {

/**
 * Initialize the core library, this must be called before
 * using mojo-core. Calls of initialize must be matched by
 * calls to deinitialize. This is necessary for modules etc
 * that cannot know of the initialization state of mojo-core.
 */
void initialize();

/**
 * @return true if mojo-core has been initialized.
 *
 * This is really only for testing, you should not depend
 * on the state of initialization returned.
 */
bool initialized();

/**
 * Deinitialize mojo-core library.
 */
void deinitialize();

M_DECLARE_LOGGER(INIT);
M_DECLARE_LOGGER(RUN_LOOP);
M_DECLARE_LOGGER(STRING_CONVERT);

} // namespace core

#endif // MOJO_CORE_CORE_INITIALIZE_H
