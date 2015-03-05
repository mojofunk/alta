#ifndef MOJO_TRACK_H
#define MOJO_TRACK_H

#ifndef MOJO_APPLICATION_AMALGAMATED
#include "mojo/core/object/object.hpp"
#endif

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

	//virtual InputBusSP get_input_bus () const = 0;

	//virtual void set_input_bus (InputBusSP) const = 0;
	
	//virtual OutputBusSP get_output_bus () const = 0;

	//virtual void set_output_bus (OutputBusSP) const = 0;
	
private:

	// member data
	std::string m_name;

public:

	static PropertyID const s_property_name_id;
};

} // namespace mojo

#endif // MOJO_TRACK_H
