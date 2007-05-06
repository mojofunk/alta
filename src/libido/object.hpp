
#ifndef LIBIDO_OBJECT_INCLUDED
#define LIBIDO_OBJECT_INCLUDED

#include <libido/types.hpp>

namespace ido {

class IObject {
public:

	virtual ~IObject() { }

	virtual const id_t get_identifier() const = 0;

	virtual void set_identifier(const id_t id) = 0;

};

}

#endif
