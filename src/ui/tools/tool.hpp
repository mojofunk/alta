
#ifndef GMOJO_TOOL_INCLUDED
#define GMOJO_TOOL_INCLUDED

namespace gmojo {

/**
 * A Tool should only depend on internal class interfaces
 */
class Tool
{
public:

	virtual const string get_name() const = 0;

	virtual void on_button_press () = 0;
	
	virtual void on_button_release () = 0;

	virtual void on_motion () = 0;

	virtual bool on_key_press () = 0;

	virtual bool on_key_release () = 0;

};

}

#endif
