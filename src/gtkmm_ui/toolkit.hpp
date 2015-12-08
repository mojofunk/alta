#ifndef UI_TOOLKIT
#define UI_TOOLKIT

namespace ui {

class Tool;
typedef std::shared_ptr<Tool> ToolSP;

class Toolkit {
public: // typedefs
	typedef std::list<ToolSP> tool_list_t;

public:
	Toolkit();

public: // API
	tool_list_t get_tools() const { return m_tools; }

	ToolSP get_current_tool() const { return m_current_tool; }

	void set_current_tool(ToolSP tool) { m_current_tool = tool; }

	void add_tool(ToolSP tool);

	void remove_tool(ToolSP tool);

protected:
	ToolSP m_current_tool;

	tool_list_t m_tools;
};

} // namespace ui

#endif
