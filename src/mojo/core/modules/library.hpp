#ifndef MOJO_LIBRARY_H
#define MOJO_LIBRARY_H

namespace mojo {

class Library {
public:
	virtual ~Library();

public:
	virtual fs::path get_filepath() const = 0;

	virtual bool open() = 0;
	virtual bool close() = 0;

	virtual std::string get_error_string() const = 0;

	virtual void* resolve(const std::string& symbol_name) = 0;

	virtual bool is_library(const fs::path& filepath) = 0;
};

LibrarySP create_library(const fs::path& filepath);

bool is_library(const fs::path& filepath);

} // namespace mojo

#endif // MOJO_LIBRARY_H
