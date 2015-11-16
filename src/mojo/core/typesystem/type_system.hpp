#ifndef MOJO_TYPE_SYSTEM_H
#define MOJO_TYPE_SYSTEM_H

// TODO make into TypeSystem class

namespace types {

void initialize();

void deinitialize();

void register_type(TypeFactorySP type);

/**
 * because std::type_info.name() is not portable between compilers
 * etc, use a standard mapping of names to types.
 */
const std::string get_type_name(const std::type_info& info);

/**
 * Given a portable type name create a specific instance of that
 * type
 */
boost::any create_type(const std::string& type_name);

} // namespace types

#endif // MOJO_TYPE_SYSTEM_H
