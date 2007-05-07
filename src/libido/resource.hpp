
#ifndef LIBIDO_RESOURCE_INCLUDED
#define LIBIDO_RESOURCE_INCLUDED

#include <libido/types.hpp>

namespace ido {

/**
 * A resource is some external data not included
 * in the project. In all cases I'm envisioning this
 * will be a file.
 */
class IResource : public IObject {
public:

	virtual const std::string& get_uri() const = 0;

	virtual void set_uri(const std::string) = 0;

};

}

#endif
