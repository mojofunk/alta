#include <liblogx/file_identifier.hpp>

namespace logx {

FileIdentifier::FileIdentifier(const string& file)
	:
		LogData(),
		m_file(file)
{

}

FileIdentifier::FileIdentifier(const FileIdentifier& other)
	:
		LogData(other),
		m_file(other.m_file)
{

}

const string
FileIdentifier::get_file_string() const
{
	return m_file;
}

ostream& operator<<(ostream& out, const FileIdentifier& file_identifier)
{
	return out << file_identifier.get_file_string();
}

} // namespace logx
