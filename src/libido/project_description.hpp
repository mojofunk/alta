
#ifndef LIBIDO_PROJECT_DESCRIPTION_HPP
#define LIBIDO_PROJECT_DESCRIPTION_HPP

#include <string>

namespace ido {

using std::string;

/**
 * A class representing a description of a Project.
 *
 */
class IProjectDescription
{
public:

	virtual ~IProjectDescription();

	virtual void set_project_name(const string& new_name) = 0;

	virtual const string& get_project_name() const = 0;

};

} // namespace ido

#endif
