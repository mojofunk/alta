

#include "toolkit.hpp"

namespace ui {

Toolkit::Toolkit ()
{ }

void
Toolkit::add_tool (ToolSP tool)
{
	m_tools.push_back (tool);
}

void
Toolkit::remove_tool (ToolSP tool)
{
	m_tools.erase (std::find(m_tools.begin(), m_tools.end(), tool));
}

} // namespace ui
