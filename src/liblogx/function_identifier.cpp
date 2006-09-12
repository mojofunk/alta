#include <liblogx/function_identifier.hpp>

namespace logx {

FunctionIdentifier::FunctionIdentifier(const string& function_signature)
	:
		LogData(),
		m_function_signature(function_signature)
{

}

FunctionIdentifier::FunctionIdentifier(const FunctionIdentifier& other)
	:
		LogData(other),
		m_function_signature(other.m_function_signature)
{

}

const string
FunctionIdentifier::get_function_string() const
{
	return m_function_signature;
}

ostream& operator<<(ostream& out, const FunctionIdentifier& function_identifier)
{
	return out << function_identifier.get_function_string();
}

} // namespace logx
