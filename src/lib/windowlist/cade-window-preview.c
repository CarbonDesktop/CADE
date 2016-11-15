#include "cade-window-preview.h"
#include <gdk/gdkx.h>
#include <data/cade-window-controller.h>

struct _CadeWindowPreview {
  GtkWindow parent_instance;
  gint win;
  GtkWidget *image;
  CadeWindowController *controller;
};

struct _CadeWindowPreviewClass {
  GtkWindowClass parent_class;
};

G_DEFINE_TYPE (CadeWindowPreview, cade_window_preview, GTK_TYPE_WINDOW)

static void
cade_window_preview_class_init (CadeWindowPreviewClass *klass)
{
}

static void _show_preview(GtkWidget *widget, gpointer data)
{
  CadeWindowPreview *self = CADE_WINDOW_PREVIEW(widget);

  GdkPixbuf *screenshot = cade_window_controller_screenshot(self->controller, self->win);
  int w = gdk_pixbuf_get_width(screenshot);
  int h = gdk_pixbuf_get_height(screenshot);

  GdkPixbuf *edit;

  if(w > h)
    edit = gdk_pixbuf_scale_simple(screenshot, 300, 200, GDK_INTERP_BILINEAR);
  else
    edit = gdk_pixbuf_scale_simple(screenshot, 300 , 200, GDK_INTERP_BILINEAR);


  gtk_image_set_from_pixbuf(GTK_IMAGE(self->image), edit);

  g_object_unref(edit);
  g_object_unref(screenshot);

  gtk_widget_show_all(widget);
}

static void
cade_window_preview_init (CadeWindowPreview *self)
{
  gtk_container_set_border_width(GTK_CONTAINER(self), 10);
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add(GTK_CONTAINER(self), box);

  self->controller = cade_window_controller_new();

  self->image = gtk_image_new_from_icon_name("gtk-unknown", GTK_ICON_SIZE_DIALOG);
  gtk_box_pack_start(GTK_BOX(box), self->image, FALSE, FALSE, 0);


  g_signal_connect(self, "show", G_CALLBACK(_show_preview), NULL);
}

CadeWindowPreview *cade_window_preview_new (gint win)
{
  CadeWindowPreview *ret = g_object_new (CADE_TYPE_WINDOW_PREVIEW, "type", GTK_WINDOW_POPUP, NULL);
  ret->win = win;
  return ret;
}
