
#ifndef UI_TOOLKIT
#define UI_TOOLKIT

#include <set>

#include <boost/shared_ptr.hpp>

namespace ui {

class Tool;
typedef boost::shared_ptr<Tool> ToolSP;

class Toolkit
{
public: // typedefs

	typedef std::set<ToolSP> tool_set_t;

public:

	Toolkit ();

public: // API

	tool_set_t get_tools () const
	{ return m_tools; }

	ToolSP get_current_tool () const
	{ return m_current_tool; }

	void set_current_tool (ToolSP tool)
	{ m_current_tool = tool; }

	void add_tool (ToolSP tool);

	void remove_tool (ToolSP tool);

protected:

	ToolSP m_current_tool;

	tool_set_t m_tools;

};

} // namespace ui

#endif
