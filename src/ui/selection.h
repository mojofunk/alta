
#ifndef UI_SELECTION
#define UI_SELECTION

#include "object.hpp"

namespace ui {

template<class T>
class ObjectSelection
{
public:

private:

	std::set<T*> m_selectables;
};

} // namespace ui

#endif
