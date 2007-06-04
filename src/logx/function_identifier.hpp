#ifndef LOGX_FUNCTION_IDENTIFIER_HEADER
#define LOGX_FUNCTION_IDENTIFIER_HEADER

#include <string>
#include <iosfwd>

#include <logx/log_data.hpp>

namespace logx {

using std::string;
using std::ostream;

class FunctionIdentifier : public LogData
{
public:

	FunctionIdentifier(const string& function_signature);

	FunctionIdentifier(const FunctionIdentifier& other);

	const string get_function_string() const;

private:

	const string m_function_signature;

};

ostream& operator<<(ostream& out, const FunctionIdentifier& function_identifier);

} // namespace logx

#endif // LOGX_FUNCTION_IDENTIFIER_HEADER
