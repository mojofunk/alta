#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"

#include "mojo/core/filesystem/search_path.hpp"
#endif

namespace {

#ifdef MOJO_WINDOWS
const char* const path_delimiter = ";";
#else
const char* const path_delimiter = ":";
#endif
}

namespace mojo {

Searchpath::Searchpath()
{
}

Searchpath::Searchpath(const std::string& path)
{
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

	boost::char_separator<char> sep(path_delimiter);

	tokenizer tokens(path, sep);

	for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end();
	     ++tok_iter) {
		add_directory(*tok_iter);
	}
}

Searchpath::Searchpath(const fs::path& path)
{
	add_directory(path);
}

Searchpath::Searchpath(const paths_t& paths)
{
	std::copy(paths.begin(), paths.end(), std::back_inserter(m_dirs));
}

Searchpath::Searchpath(const std::vector<std::string>& paths)
{
	std::copy(paths.begin(), paths.end(), std::back_inserter(m_dirs));
}

Searchpath::Searchpath(const Searchpath& other)
    : m_dirs(other.m_dirs)
{
}

void Searchpath::add_directory(const fs::path& directory_path)
{
	// test for existance and warn etc?
	m_dirs.push_back(directory_path);
}

const std::string Searchpath::to_string() const
{
	std::string path;

	for (const_iterator i = m_dirs.begin(); i != m_dirs.end(); ++i) {
		path += (*i).string();
		path += path_delimiter;
	}

	path = path.substr(0, path.length() - 1); // drop final separator

	return path;
}

Searchpath& Searchpath::operator=(const Searchpath& path)
{
	m_dirs = path.m_dirs;
	return *this;
}

Searchpath& Searchpath::operator+=(const Searchpath& spath)
{
	m_dirs.insert(m_dirs.end(), spath.m_dirs.begin(), spath.m_dirs.end());
	return *this;
}

Searchpath& Searchpath::operator+=(const fs::path& directory_path)
{
	add_directory(directory_path);
	return *this;
}

Searchpath& Searchpath::operator+(const fs::path& directory_path)
{
	add_directory(directory_path);
	return *this;
}

Searchpath& Searchpath::operator+(const Searchpath& spath)
{
	// concatenate paths into new Searchpath
	m_dirs.insert(m_dirs.end(), spath.m_dirs.begin(), spath.m_dirs.end());
	return *this;
}

Searchpath& Searchpath::add_subdirectory_to_paths(const std::string& subdir)
{
	paths_t tmp;
	std::string directory_path;

	for (iterator i = m_dirs.begin(); i != m_dirs.end(); ++i) {
		// should these new paths just be added to the end of
		// the search path rather than replace?
		*i /= subdir;
	}

	return *this;
}

Searchpath& Searchpath::operator/(const std::string& subdir)
{
	return add_subdirectory_to_paths(subdir);
}

} // namespace mojo
