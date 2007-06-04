#ifndef LOGX_LINE_IDENTIFIER_HEADER
#define LOGX_LINE_IDENTIFIER_HEADER

#include <string>
#include <iosfwd>

#include <logx/log_data.hpp>

namespace logx {

using std::string;
using std::ostream;

class LineIdentifier : LogData
{
public:

	LineIdentifier(const int line);

	LineIdentifier(const LineIdentifier& other);

	const string get_line_string() const;

	const unsigned int get_line_number() const;

private:

	const unsigned int m_line_number;

	static const string get_string_from_line_number(const unsigned int line_number);

};

ostream& operator<<(ostream& out, const LineIdentifier& line_identifier);

} // namespace logx

#endif // LOGX_LINE_IDENTIFIER_HEADER

