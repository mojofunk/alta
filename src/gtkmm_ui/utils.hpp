#ifndef UI_UTILS
#define UI_UTILS

namespace ui {

ActionGPtr get_action(BuilderGPtr& builder, const std::string& name);

ToggleActionGPtr get_toggleaction(BuilderGPtr& builder,
                                  const std::string& name);

void connect_action(BuilderGPtr& builder,
                    const std::string& name,
                    const sigc::slot<void>& slot);

void connect_toggleaction(BuilderGPtr& builder,
                          const std::string& name,
                          const sigc::slot<void>& slot);
}

#endif
