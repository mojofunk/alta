#include <liblogx/thread_identifier.hpp>

namespace logx {

ThreadIdentifier::ThreadIdentifier (const string& identifier)
	:
		LogData(),
		m_identifier(identifier)
{ }

ThreadIdentifier::ThreadIdentifier (const ThreadIdentifier& other)
	:
		LogData(),
		m_identifier(other.m_identifier)
{ }

const string&
ThreadIdentifier::get_thread_string () const
{ return m_identifier; }

ostream& operator<<(ostream& out, const ThreadIdentifier& thread_identifier)
{
	return out << thread_identifier.get_thread_string();
}

} // namespace logx
