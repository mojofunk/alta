
#ifndef BLING_GLADE_FACTORY_INCLUDED
#define BLING_GLADE_FACTORY_INCLUDED

#include <string>
#include <libglademm/xml.h>

namespace bling {

typedef Glib::RefPtr<Gnome::Glade::Xml> GladeRef;

/**
   This is the base class for all glade 
   factories so that the same domain is
   used.
*/
class GladeFactory {
	
protected:
	static GladeRef
	create(const std::string& full_path,
	       const Glib::ustring& toplevel_widget = Glib::ustring());
};

} // namespace bling

#endif // BLING_GLADE_FACTORY_INCLUDED
