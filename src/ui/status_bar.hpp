
#ifndef GMOJO_STATUS_BAR
#define GMOJO_STATUS_BAR

#include <ui/widget.hpp>

namespace gmojo {

class StatusBar : public Widget
{
public: // constructors

	StatusBar ();

public: // widget interface

	virtual GtkWidget* get_widget () const
	{ return m_statusbar; }

private: // member data

	GtkWidget* m_statusbar;

};

} // namespace gmojo

#endif
