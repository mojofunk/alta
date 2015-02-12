#ifndef MOJO_NULL_DELETER_H
#define MOJO_NULL_DELETER_H

namespace mojo {

namespace internal {

struct null_deleter
{
	void operator()(void const *) const { }
};

}

}

#endif // MOJO_NULL_DELETER_H
