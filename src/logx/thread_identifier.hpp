#ifndef LOGX_THREAD_IDENTIFIER_HEADER
#define LOGX_THREAD_IDENTIFIER_HEADER

#include <string>
#include <iosfwd>

#include <logx/log_data.hpp>

namespace logx {

using std::string;
using std::ostream;

class ThreadIdentifier : public LogData
{
public:

	ThreadIdentifier(const string& identifier);

	ThreadIdentifier(const ThreadIdentifier& other);

	const string&       get_thread_string() const;

private:
	
	const string         m_identifier;

};

ostream& operator<<(ostream& out, const ThreadIdentifier& thread_identifier);

} // namespace logx

#endif // LOGX_THREAD_IDENTIFIER_HEADER
