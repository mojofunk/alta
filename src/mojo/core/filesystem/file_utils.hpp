#ifndef MOJO_FILE_UTILS_H
#define MOJO_FILE_UTILS_H

/**
 * \return true if the file matches
 */
typedef bool (*FileMatchFunc)(const fs::path& file_path);

std::size_t
find_matching_files(const std::vector<fs::path>& directory_paths,
                    FileMatchFunc match_functor,
                    std::vector<fs::path>& result);

std::size_t
find_matching_files(const fs::path& directory_path,
                    FileMatchFunc match_functor,
                    std::vector<fs::path>& result);
std::size_t
find_matching_file(const std::vector<fs::path>& paths,
                   const std::string& filename,
                   std::vector<fs::path>& result);

std::size_t
find_matching_file(const fs::path& paths,
                   const std::string& filename,
                   std::vector<fs::path>& result);

bool
find_matching_file(const fs::path& paths,
                   const std::string& filename,
                   fs::path& result);

/**
 * Given a full path to a file that may or may not exist,
 * return a unique non-existing file path.
 */
const fs::path
get_non_existent_file_path(const fs::path& file_path);

fs::path
tmp_writable_directory(const char* domain, const std::string& prefix);

#endif // MOJO_FILE_UTILS_H
