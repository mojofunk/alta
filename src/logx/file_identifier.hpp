#ifndef LOGX_FILE_IDENTIFIER_HEADER
#define LOGX_FILE_IDENTIFIER_HEADER

#include <string>
#include <iosfwd>

#include <logx/log_data.hpp>

namespace logx {

using std::string;
using std::ostream;

class FileIdentifier : public LogData
{
public:

	FileIdentifier(const string& file);

	FileIdentifier(const FileIdentifier& other);

	const string get_file_string() const;

	//const string get_file_name() const;
	//const string get_file_path() const;
	
private:

	const string m_file;

};

ostream& operator<<(ostream& out, const FileIdentifier& file_identifier);

} // namespace logx

#endif // LOGX_FILE_IDENTIFIER_HEADER
