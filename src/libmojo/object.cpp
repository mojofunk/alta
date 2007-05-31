
#include <libmojo/object.hpp>

#include <libmojo/debug.hpp>

namespace mojo {

Object::Object ()
	:
		m_ref_count(1)
{
#ifdef MOJO_DEBUG_EXTRA
		LOG_MOJO_DEBUG << "refcount" << m_ref_count.get();
#endif

}

Object::~Object ()
{
#ifdef MOJO_DEBUG_EXTRA
		LOG_MOJO_DEBUG << "refcount" << m_ref_count.get();
#endif

}

void
Object::ref ()
{
#ifdef MOJO_DEBUG_EXTRA
		LOG_MOJO_DEBUG << "refcount" << m_ref_count.get();
#endif
	++m_ref_count;
}

void
Object::unref ()
{
	--m_ref_count;

#ifdef MOJO_DEBUG_EXTRA
		LOG_MOJO_DEBUG << "refcount" << m_ref_count.get();
#endif

	if(m_ref_count.get() == 0)
	{
		dispose();
		delete this;
	}
}

} // namespace mojo
