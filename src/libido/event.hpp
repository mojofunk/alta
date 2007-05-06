
#ifndef LIBIDO_EVENT_INCLUDED
#define LIBIDO_EVENT_INCLUDED

#include <libido/types.hpp>
#include <libido/object.hpp>

namespace ido {

class IEvent : public IObject
{
public:

	virtual const position_t get_position() = 0;

	virtual bool set_position(const position_t) = 0;

};

} // namespace ido

#endif
