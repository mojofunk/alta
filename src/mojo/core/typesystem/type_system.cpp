using Types = std::set<mojo::TypeFactorySP>;

std::atomic_uint s_init_typesystem_count(0);

Types* s_types(0);

TypeRegistry* s_type_registry(0);

void register_builtin_types()
{
	types::register_type(TypeFactorySP(
	    new TemplateTypeFactory<int32_t>(TypeNames::int32_type_name)));
	types::register_type(TypeFactorySP(
	    new TemplateTypeFactory<int64_t>(TypeNames::int64_type_name)));
	types::register_type(
	    TypeFactorySP(new TemplateTypeFactory<float>(TypeNames::float_type_name)));
	types::register_type(TypeFactorySP(
	    new TemplateTypeFactory<std::string>(TypeNames::string_type_name)));
}

namespace types {

void initialize()
{
	if (++s_init_typesystem_count != 1) return;
	s_types = new Types;
	s_type_registry = new TypeRegistry;
	register_builtin_types();
}

void deinitialize()
{
	if (--s_init_typesystem_count != 0) return;
	delete s_type_registry;
	s_type_registry = 0;
	delete s_types;
	s_types = 0;
}

void register_type(TypeFactorySP type)
{
	s_type_registry->set_type_name(type->type_info(), type->type_name());
	s_types->insert(type);
}

const std::string get_type_name(const std::type_info& info)
{
	return s_type_registry->get_type_name(info);
}

boost::any create_type(const std::string& type_name)
{
	for (Types::const_iterator i = s_types->begin(); i != s_types->end(); ++i) {
		if ((*i)->type_name() == type_name) return (*i)->create();
	}

	return boost::any();
}

} // namespace types
