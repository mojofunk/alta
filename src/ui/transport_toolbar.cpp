
#include <ui/transport_toolbar.hpp>

#include <iostream>

using namespace std;

namespace gmojo {

TransportToolbar::TransportToolbar ()
	: m_hbox(gtk_hbox_new (FALSE, 0))
	  , m_hbuttonbox(gtk_hbutton_box_new ())
	  , m_loop_button(gtk_toggle_button_new_with_label ("Loop")) 
	  , m_stop_button(gtk_toggle_button_new_with_label ("Stop")) 
	  , m_play_button(gtk_toggle_button_new_with_label ("Play")) 
{
	gtk_box_pack_start (GTK_BOX (m_hbuttonbox), m_loop_button,
		   	false, false, 0);

	gtk_box_pack_start (GTK_BOX (m_hbuttonbox), m_stop_button,
		   	false, false, 0);

	gtk_box_pack_start (GTK_BOX (m_hbuttonbox), m_play_button,
		   	false, false, 0);

	gtk_box_pack_start (GTK_BOX (m_hbox), m_hbuttonbox,
			false, false, 0);

	gtk_widget_show_all (m_hbox);

	g_signal_connect (m_loop_button, "toggled",
			G_CALLBACK (TransportToolbar::button_toggled), this);
	g_signal_connect (m_stop_button, "toggled",
			G_CALLBACK (TransportToolbar::button_toggled), this);
	g_signal_connect (m_play_button, "toggled",
			G_CALLBACK (TransportToolbar::button_toggled), this);

}

void
TransportToolbar::button_toggled (GtkToggleButton *togglebutton,
		gpointer data)
{
	    TransportToolbar* toolbar = static_cast<TransportToolbar*>(data);
		return toolbar->on_button_toggled (togglebutton);
}

void
TransportToolbar::on_button_toggled (GtkToggleButton *togglebutton)
{
	GtkWidget* button = GTK_WIDGET (togglebutton);
	bool active = gtk_toggle_button_get_active (togglebutton);

	if (button == m_loop_button)
	{
		if (active)
		{
			cerr << "loop activated" << endl;
		}
		else
		{
			cerr << "loop deactivated" << endl;
		}
	}
   	else if (button == m_stop_button)
	{
		if (active) 
		{
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (m_play_button), FALSE);

			cerr << "stop button activated" << endl;
		}
		else
		{
			if (!gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (m_play_button)))
			{
				gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (m_stop_button), TRUE);
			}
			else
			{
				cerr << "stop button deactivated" << endl;
			}
		}
	}
	else
	{
		if (active)
		{
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (m_stop_button), FALSE);
			cerr << "play button activated" << endl;
		}
		else
		{
			if (!gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (m_stop_button)))
			{
				gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (m_play_button), TRUE);
			}
			else
			{
				cerr << "play button deactivated" << endl;
			}
		}
	}
}

} // namespace gmojo


