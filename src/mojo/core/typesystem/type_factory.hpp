#ifndef MOJO_TYPE_FACTORY_H
#define MOJO_TYPE_FACTORY_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#endif

namespace mojo {

class TypeFactory {
public:
	virtual std::string type_name() const = 0;

	/// create always returns a pointer to a newly
	/// allocated type.
	virtual boost::any create() const = 0;

	virtual const std::type_info& type_info() const = 0;

protected:
	virtual ~TypeFactory() {}
};

} // namespace mojo

#endif // MOJO_TYPE_FACTORY_H
