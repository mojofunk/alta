#ifndef UI_TIMERS
#define UI_TIMERS

namespace ui {

sigc::connection slow_timer_connect(const sigc::slot<void>& slot);

sigc::connection fast_timer_connect(const sigc::slot<void>& slot);

sigc::connection rapid_timer_connect(const sigc::slot<void>& slot);

sigc::connection blink_timer_connect(const sigc::slot<void, bool>& slot);

} // namespace ui

#endif
