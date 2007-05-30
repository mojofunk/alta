#include <liblogx/pretty_formatter.hpp>

namespace logx {

PrettyFormatter::PrettyFormatter(const vector<string>& log_data)
	:
		m_log_data(log_data)
{ }
	
ostream&
PrettyFormatter::operator()(ostream& out) const
{
	const string separator(" : ");
	const unsigned int max_column_width = 50;

	for(const_iterator iter = m_log_data.begin(),
			end = m_log_data.end(); iter != end; ++iter)
	{
		if(iter != m_log_data.begin()) {
			out << separator;
		}

		out
			<< std::left
			<< iter->substr(0, max_column_width);

	}
	return out;
}

ostream& operator<<(ostream& out, PrettyFormatter& formatter)
{
	return formatter(out);
}

} // namespace logx
