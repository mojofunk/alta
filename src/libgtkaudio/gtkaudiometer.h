#ifndef GTK_AUDIO_METER_H
#define GTK_AUDIO_METER_H

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gtk/gtkwidget.h>

G_BEGIN_DECLS

#define GTK_TYPE_AUDIO_METER            (gtk_audio_meter_get_type ())
#define GTK_AUDIO_METER(obj)            (GTK_CHECK_CAST ((obj), GTK_TYPE_AUDIO_METER, GtkAudioMeter))
#define GTK_AUDIO_METER_CLASS(klass)    (GTK_CHECK_CLASS_CAST ((klass), GTK_TYPE_AUDIO_METER, GtkAudioMeterClass))
#define GTK_IS_AUDIO_METER(obj)         (GTK_CHECK_TYPE ((obj), GTK_TYPE_AUDIO_METER))
#define GTK_IS_AUDIO_METER_CLASS(klass) (GTK_CHECK_CLASS_TYPE ((klass), GTK_TYPE_AUDIO_METER))
#define GTK_AUDIO_METER_GET_CLASS(obj)  (GTK_CHECK_GET_CLASS ((obj), GTK_TYPE_AUDIO_METER, GtkAudioMeterClass))

typedef struct _GtkAudioMeter       GtkAudioMeter;
typedef struct _GtkAudioMeterClass  GtkAudioMeterClass;

struct _GtkAudioMeter
{
  GtkDrawingArea widget;

  gdouble	level;
  gdouble	peak;
  gint		hold_count;

/*
  guint		low_color; // green by default
  guint		mid_color; // yellow by default
  guint		peak_color; // red by default
*/

/*
  gdouble 	low_stop;
  gdouble	mid_stop;
  gdouble	high_stop;
*/
};

struct _GtkAudioMeterClass
{
  GtkDrawingAreaClass parent_class;

  /* < private > */
};

GtkWidget* gtk_audio_meter_new (void);

G_END_DECLS

#endif /* GTK_AUDIO_METER_H */
