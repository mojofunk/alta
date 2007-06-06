
#include <boost/tokenizer.hpp>

#include <booty/search_path.hpp>

namespace {

#ifdef WIN32
const char * const path_delimiter = ";";
#else
const char * const path_delimiter = ":";
#endif

}

namespace booty {


SearchPath::SearchPath ()
{

}

SearchPath::SearchPath (const string& path)
{
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> sep(path_delimiter);

	tokenizer tokens(path, sep);

	for (
			tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end();
			++tok_iter
		)
	{
		add_directory (*tok_iter);
	}
}

SearchPath::SearchPath (const vector<fs::path>& paths)
{
	add_directories (paths);
}

SearchPath::SearchPath (const SearchPath& other)
	: m_dirs(other.m_dirs)
{

}

void
SearchPath::add_directory (const fs::path& directory_path)
{
	// test for existance and warn etc?
	m_dirs.push_back(directory_path);
}

void
SearchPath::add_directories (const vector<fs::path>& paths)
{
	for(vector<fs::path>::const_iterator i = paths.begin(); i != paths.end(); ++i) {
		add_directory (*i);
	}
}

const string
SearchPath::get_search_path_string () const
{
	string path;

	for (vector<fs::path>::const_iterator i = m_dirs.begin(); i != m_dirs.end(); ++i) {
		path += (*i).string();
		path += path_delimiter;
	}

	path = path.substr (0, path.length() - 1); // drop final separator

	return path;
}

SearchPath&
SearchPath::operator= (const SearchPath& path)
{
	m_dirs = path.m_dirs;
	return *this;
}

SearchPath& 
SearchPath::operator+= (const SearchPath& spath)
{
	m_dirs.insert(m_dirs.end(), spath.m_dirs.begin(), spath.m_dirs.end());
	return *this;
}

SearchPath& 
SearchPath::operator+= (const fs::path& directory_path)
{
	add_directory (directory_path);
	return *this;
}

SearchPath& 
SearchPath::operator+ (const fs::path& directory_path)
{
	add_directory (directory_path);
	return *this;
}

SearchPath& 
SearchPath::operator+ (const SearchPath& spath)
{
	// concatenate paths into new SearchPath
	m_dirs.insert(m_dirs.end(), spath.m_dirs.begin(), spath.m_dirs.end());
	return *this;
}

SearchPath&
SearchPath::add_subdirectory_to_paths (const string& subdir)
{
	vector<fs::path> tmp;
	string directory_path;

	for (vector<fs::path>::iterator i = m_dirs.begin(); i != m_dirs.end(); ++i)
	{
		// should these new paths just be added to the end of 
		// the search path rather than replace?
		*i /= subdir;
	}
	
	return *this;
}
	
SearchPath&
SearchPath::operator/ (const string& subdir)
{
	return add_subdirectory_to_paths (subdir);
}

} // namespace booty
