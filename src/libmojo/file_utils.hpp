
#ifndef MOJO_FILE_UTILS_INCLUDED
#define MOJO_FILE_UTILS_INCLUDED

#include <string>

namespace mojo {

using std::string;

/**
 * Given a directory, file name and file extension get a string
 * representing the first non-existing file name containing name, a
 * hyphen, a number(greater than zero) and the file extension.
 * 
 * i.e. name-1.txt
 *
 * \todo legalize characters, I18N, etc.
 *
 */
const string get_unique_filename (const string& directory,
                                  const string& name,
                                  const string& extension);

} // namespace mojo

#endif // MOJO_FILE_UTILS_INCLUDED
