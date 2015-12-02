#include "utils.hpp"

namespace ui {

ActionGPtr get_action(BuilderGPtr& builder, const std::string& name)
{
	ObjectGPtr obj = builder->get_object(name);
	assert(obj);
	return ActionGPtr::cast_dynamic(obj);
}

ToggleActionGPtr get_toggleaction(BuilderGPtr& builder, const std::string& name)
{
	ObjectGPtr obj = builder->get_object(name);
	assert(obj);
	return ToggleActionGPtr::cast_dynamic(obj);
}

void connect_action(BuilderGPtr& builder,
                    const std::string& name,
                    const sigc::slot<void>& slot)
{
	ActionGPtr action = get_action(builder, name);

	assert(action);

	action->signal_activate().connect(slot);
}

void connect_toggleaction(BuilderGPtr& builder,
                          const std::string& name,
                          const sigc::slot<void>& slot)
{
	ToggleActionGPtr action = get_toggleaction(builder, name);

	assert(action);

	action->signal_activate().connect(slot);
}

} // namespace ui
