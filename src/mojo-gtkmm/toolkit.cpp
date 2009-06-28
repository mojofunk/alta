

#include "toolkit.hpp"

namespace ui {

Toolkit::Toolkit ()
{ }

void
Toolkit::add_tool (ToolSP tool)
{
	m_tools.insert (tool);
}

void
Toolkit::remove_tool (ToolSP tool)
{
	m_tools.erase (tool);

}

} // namespace ui
