
#include <gtk/gtk.h>

#include <glib.h>
#include <glib/gprintf.h>

void
on_quit_activate (GtkAction *action, gpointer data)
{
	g_printf ("on_quit_activate called\n");
	gtk_main_quit ();
}

char *
get_ui_file_path (const char *filename)
{
	char *path = NULL;

	path = g_build_filename ("data", filename, NULL);

	g_printf ("%s\n", path);

	if (g_file_test (path, G_FILE_TEST_EXISTS) == FALSE)
	{
		return NULL;
	}
	return path;
}

GtkBuilder*
create_builder_using_file (const char* filename)
{
	GtkBuilder *builder = NULL;
	GError *error = NULL;

	builder = gtk_builder_new ();

	if (builder == NULL) return NULL;
   	
	if (gtk_builder_add_from_file (builder, filename, &error) == FALSE)
	{
		g_printf ("%s\n", error->message);
		g_error_free (error);

		return NULL;
	}

	//gtk_builder_connect_signals (builder, NULL);

	return builder;
}

int
main(int argc, char *argv[])
{
	char * ui_file = NULL;
	GtkWidget *window = NULL;
	GtkBuilder *builder = NULL;
	GtkAction *action = NULL;

	gtk_init (&argc, &argv);

	ui_file = get_ui_file_path ("gmojo.ui");

	builder = create_builder_using_file (ui_file);

	window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));

	action = GTK_ACTION (gtk_builder_get_object (builder, "quit"));

	g_signal_connect (G_OBJECT (action), "activate", G_CALLBACK
			(on_quit_activate), NULL);

	gtk_widget_show_all (window);

	gtk_main ();

	g_free (ui_file);

	return 0;
}
