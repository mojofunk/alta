
#ifndef MOJO_TRACK
#define MOJO_TRACK

#include <mojo/object.hpp>

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

public:

	void set_name (const std::string& name);
	
private:

	// member data
	std::string m_name;

private:

	static const char * const s_property_name;
};

} // namespace mojo

#endif
