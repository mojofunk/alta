
#ifndef ARK_TYPE_NAME_REGISTRY_INCLUDED
#define ARK_TYPE_NAME_REGISTRY_INCLUDED

#include <string>
#include <typeinfo>

namespace ark {

using std::string;

/**
 * This class is needed because serialization backends need to be able
 * to create class instances when an archive is reconstructed. To do
 * that the client code uses a TypeFactory that maps object names to
 * types. Using std::type_info.name() is not sufficient as it is not
 * portable between compilers or languages.
 */
class TypeNameRegistry
{
public:

	/**
	 * because std::type_info.name() is not portable between compilers
	 * etc, use a standard mapping of names to types.
	 */
	virtual const string type_name (const std::type_info& info) const = 0;

	virtual ~TypeNameRegistry() { }
};

} // namespace ark

#endif
