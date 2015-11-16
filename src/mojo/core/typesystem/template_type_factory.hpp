#ifndef MOJO_TEMPLATE_TYPE_FACTORY_H
#define MOJO_TEMPLATE_TYPE_FACTORY_H

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

#endif // MOJO_TEMPLATE_TYPE_FACTORY_H
