
#ifndef UI_UTILS
#define UI_UTILS

#include "types.hpp"

namespace ui {

ActionPtr get_action (BuilderPtr& builder, const std::string& name);

ToggleActionPtr get_toggleaction (BuilderPtr& builder,
	   	const std::string& name);

void connect_action (BuilderPtr& builder,
		const std::string& name, const sigc::slot<void>& slot);

void connect_toggleaction (BuilderPtr& builder,
	   	const std::string& name, const sigc::slot<void>& slot);

}

#endif
