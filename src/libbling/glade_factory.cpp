
#include <iostream>

#include "glade_factory.hpp"

namespace bling {

Glib::RefPtr<Gnome::Glade::Xml>
GladeFactory::create(const std::string& full_path_to_file,
                     const Glib::ustring& toplevel_widget)
{
	try {
		return Gnome::Glade::Xml::create(full_path_to_file,
                                         toplevel_widget,
                                         PACKAGE_NAME );
	} catch(const Gnome::Glade::XmlError& ex) {
		std::cerr << ex.what() << std::endl;
		throw ex;
	}
}

} // namespace bling
