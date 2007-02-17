#include <boost/noncopyable.hpp>

#include "project.hpp"

namespace mojo {

class project::impl : boost::noncopyable
{
public:



};

project::project()
	: m_pimpl(new impl)
{


}

project::~project()
{


}

} // namespace mojo
