#ifndef MOJO_NULL_DELETER
#define MOJO_NULL_DELETER

namespace mojo {

namespace internal {

struct null_deleter
{
	void operator()(void const *) const { }
};

}

}

#endif
