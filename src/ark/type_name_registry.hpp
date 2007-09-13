
#ifndef ARK_TYPE_NAME_REGISTRY_INCLUDED
#define ARK_TYPE_NAME_REGISTRY_INCLUDED

namespace ark {

class TypeNameRegistry
{
public:

	/**
	 * because std::type_info.name() is not portable between compilers
	 * etc, use a standard mapping of names to types.
	 */
	virtual const string type_name (const std::type_info& info) = 0;

protected:

	virtual ~TypeNameRegistry() { }

};

} // namespace ark

#endif
