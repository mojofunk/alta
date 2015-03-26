#ifndef MOJO_TEMPLATE_TYPE_FACTORY_H
#define MOJO_TEMPLATE_TYPE_FACTORY_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#include "mojo/core/typesystem/type_factory.hpp"
#endif

namespace mojo {

template <class T>
class TemplateTypeFactory : public TypeFactory {
public:
	TemplateTypeFactory(const std::string& type_name)
	    : m_type_name(type_name)
	{
	}

	virtual std::string type_name() const { return m_type_name; }

	virtual boost::any create() const { return boost::any(new T); }

	virtual const std::type_info& type_info() const { return typeid(T); }

private:
	const std::string m_type_name;
};

} // namespace mojo

#endif // MOJO_TEMPLATE_TYPE_FACTORY_H
