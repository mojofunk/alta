#include "gtkaudio/gtkaudiometer.h"
#include <math.h>


// these should different for gtkvaudiometer and gtkhaudiometer
#define MIN_HORIZONTAL_BAR_WIDTH   150
#define MIN_HORIZONTAL_BAR_HEIGHT  20
#define MIN_VERTICAL_BAR_WIDTH     22
#define MIN_VERTICAL_BAR_HEIGHT    80

enum {
  PROP_0,
  PROP_LEVEL,
  PROP_HOLD_COUNT,
  PROP_PEAK,
  PROP_LOW_STOP_RGBA,
  PROP_MID_STOP_RGBA,
  PROP_HIGH_STOP_RGBA,
  PROP_LOW_STOP_POSITION,
  PROP_MID_STOP_POSITION,
  PROP_HIGH_STOP_POSITION
};

G_DEFINE_TYPE (GtkAudioMeter, gtk_audio_meter, GTK_TYPE_DRAWING_AREA);

static gint gtk_audio_meter_expose        (GtkWidget      *widget,
					  GdkEventExpose *event);

static void
gtk_audio_meter_class_init (GtkAudioMeterClass *class)
{
  GtkWidgetClass *widget_class;

  widget_class = GTK_WIDGET_CLASS(class);
  
  widget_class->expose_event = gtk_audio_meter_expose;
}

static void
gtk_audio_meter_init (GtkAudioMeter *audiometer)
{
//  audiometer->backing_store = NULL;
// audiometer->value = 0.0f;
//  audiometer->hold = 0;
}

static void
draw (GtkWidget *meter, cairo_t *cr)
{
	/*
	  Initially just fill the background in black and draw a
	  rectangle indicating the level. When the level is updated
	  and the new level is less than the old, draw a gradient 
	  between new and old. 
	  
	  fancy gradients can be added later.
	*/	

	cairo_set_source_rgb (cr, 0, 0, 0);

	cairo_rectangle(cr,
					meter->allocation.x,
					meter->allocation.y,
					meter->allocation.x + meter->allocation.width,
					meter->allocation.y + meter->allocation.height);

	
	cairo_stroke(cr);
}

GtkWidget*
gtk_audio_meter_new (void)
{
	return g_object_new (GTK_TYPE_AUDIO_METER, NULL);
}

static gint
gtk_audio_meter_expose (GtkWidget      *meter,
		  	GdkEventExpose *event)
{
	cairo_t *cr;

	cr = gdk_cairo_create (meter->window);

	cairo_rectangle (cr,
			event->area.x, event->area.y,
			event->area.width, event->area.height);

	cairo_clip (cr);
		
	draw(meter, cr);
		
	cairo_destroy (cr);

	return FALSE;
}

