#include <iostream>

#include <sstream>

#include <logx/line_identifier.hpp>

namespace logx {

using std::ostringstream;
using std::istringstream;

// static
const string
LineIdentifier::get_string_from_line_number(const unsigned int line_number)
{
	ostringstream osstr;

	osstr << line_number;

	return osstr.str();
}

LineIdentifier::LineIdentifier(const int line_number)
	:
		LogData(),
		m_line_number(line_number)
{

}

LineIdentifier::LineIdentifier(const LineIdentifier& other)
	:
		LogData(),
		m_line_number(other.m_line_number)
{


}

const string
LineIdentifier::get_line_string() const
{
	return get_string_from_line_number(m_line_number);
}

const unsigned int
LineIdentifier::get_line_number() const
{
	return m_line_number;
}

ostream& operator<<(ostream& out, const LineIdentifier& line_identifier)
{
	return out << line_identifier.get_line_string();
}

} // namespace logx
