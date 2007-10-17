
#include <rtg/node.hpp>

namespace rtg {

bool
Node::is_source () const
{
	return true;
}

bool
Node::is_sink () const
{
	return true;
}

}
