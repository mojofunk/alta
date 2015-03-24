#ifndef MOJO_CORE_CORE_INITIALIZER_H
#define MOJO_CORE_CORE_INITIALIZER_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#endif

namespace mojo {

class MOJO_API CoreInitializer {
public:

	CoreInitializer ();
	~CoreInitializer ();

	static bool initialized ();

private:

	static bool initialize ();

	static void deinitialize ();

	static std::atomic_uint m_init_count;

};

} // namespace mojo

#endif // MOJO_CORE_CORE_INITIALIZER_H
