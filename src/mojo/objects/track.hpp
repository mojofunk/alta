
#ifndef MOJO_TRACK
#define MOJO_TRACK

#include <mojo/objects/object.hpp>

namespace mojo {

class Track : public Object
{
public:

	// constructors
	Track ();

public: // Object Interface

	virtual void get_properties (Properties& props) const;

	virtual void set_properties (const Properties& props);

public:

	std::string get_name () const;

	void set_name (const std::string& name);

	//virtual InputBusSPtr get_input_bus () const = 0;

	//virtual void set_input_bus (InputBusSPtr) const = 0;
	
	//virtual OutputBusSPtr get_output_bus () const = 0;

	//virtual void set_output_bus (OutputBusSPtr) const = 0;
	
private:

	// member data
	std::string m_name;

private:

	static const char * const s_property_name;
};

} // namespace mojo

#endif
