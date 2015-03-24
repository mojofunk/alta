#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#include "mojo/core/typesystem/type_names.hpp"
#include "mojo/core/typesystem/type_system.hpp"
#include "mojo/core/typesystem/type_registry.hpp"
#include "mojo/core/typesystem/type_factory.hpp"
#include "mojo/core/typesystem/template_type_factory.hpp"
#endif

using Types = std::set<mojo::TypeFactorySP>;

namespace {

using namespace mojo;

std::atomic_uint s_init_typesystem_count(0);

Types* s_types(0);

TypeRegistry* s_type_registry(0);

void
register_builtin_types ()
{
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<int32_t>(int32_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<int64_t>(int64_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<float>(float_type_name)));
	TypeSystem::register_type (TypeFactorySP(new TemplateTypeFactory<std::string>(string_type_name)));
}

} // anon namespace

namespace mojo {

void
TypeSystem::initialize ()
{
	if (++s_init_typesystem_count != 1) return;
	s_types = new Types;
	s_type_registry = new TypeRegistry;
	register_builtin_types ();
}

void
TypeSystem::deinitialize ()
{
	if (--s_init_typesystem_count != 0) return;
	delete s_type_registry;
	s_type_registry = 0;
	delete s_types;
	s_types = 0;
}

void
TypeSystem::register_type (TypeFactorySP type)
{
	s_type_registry->set_type_name (type->type_info(), type->type_name());
	s_types->insert(type);
}

const std::string
TypeSystem::get_type_name (const std::type_info& info)
{
	return s_type_registry->get_type_name (info);
}

boost::any
TypeSystem::create_type (const std::string& type_name)
{
	for (Types::const_iterator i = s_types->begin();
			i != s_types->end(); ++i)
	{
		if ((*i)->type_name() == type_name) return (*i)->create();
	}

	return boost::any();
}

} // namespace mojo
