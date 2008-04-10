
#include <cassert>

#include "utils.hpp"

namespace ui {

ActionPtr
get_action (BuilderPtr& builder, const std::string& name)
{
	ObjectPtr obj = builder->get_object (name);
	return ActionPtr::cast_dynamic (obj);
}

ToggleActionPtr
get_toggleaction (BuilderPtr& builder, const std::string& name)
{
	ObjectPtr obj = builder->get_object (name);
	return ToggleActionPtr::cast_dynamic (obj);
}

void
connect_action (BuilderPtr& builder, const std::string& name, 
	   	const sigc::slot<void>& slot)
{
	ActionPtr action = get_action (builder, name);

	assert (action);

	action->signal_activate().connect (slot);

}

void
connect_toggleaction (BuilderPtr& builder, const std::string& name, 
	   	const sigc::slot<void>& slot)
{
	ToggleActionPtr action = get_toggleaction (builder, name);

	assert (action);

	action->signal_activate().connect (slot);
}

} // namespace ui
