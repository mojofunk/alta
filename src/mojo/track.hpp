
#ifndef MOJO_TRACK_INCLUDED
#define MOJO_TRACK_INCLUDED

#include <mojo/object.hpp>

namespace mojo {

class Track : public Object
{
public:

	// constructors
	Track ();

public:

	virtual void get_property (const std::string& name,
			boost::any& value) const;

	virtual std::vector<std::string> get_property_names () const;

	virtual void set_property (const std::string& name,
			const boost::any& value);

public:

	std::string get_name () const;

public:

	void set_name (const std::string& name);
	
private:

	// member data
	std::string m_name;

};

} // namespace mojo

#endif
