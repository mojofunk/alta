
#ifndef GMOJO_TRANSPORT_TOOLBAR
#define GMOJO_TRANSPORT_TOOLBAR

#include <ui/widget.hpp>

namespace gmojo {

class TransportToolbar : public Widget
{
public: // constructors

	TransportToolbar ();

public: // widget interface

	virtual GtkWidget* get_widget () const
	{ return m_hbox; }

public: // callbacks

	static void button_toggled (GtkToggleButton*, gpointer);

	void on_button_toggled (GtkToggleButton*);

private: // member data

	//TransportController* m_transport;

	GtkWidget* m_hbox;

	GtkWidget* m_hbuttonbox;

	GtkWidget* m_loop_button;
	GtkWidget* m_stop_button;
	GtkWidget* m_play_button;

};

} // namespace gmojo

#endif
