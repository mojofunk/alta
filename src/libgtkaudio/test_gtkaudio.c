#include <gtk/gtk.h>

#include "gtkaudiometer.h"

int
main (int argc, char **argv)
{
	GtkWidget *window;
	GtkWidget *meter;

	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	meter = gtk_audio_meter_new ();
	gtk_container_add (GTK_CONTAINER (window), meter);

	g_signal_connect (window, "destroy", 
			G_CALLBACK (gtk_main_quit), NULL);

	gtk_widget_show_all (window);

	gtk_main();

	return 0;
}
