/**
* @Author: Marius Messerschmidt <marius>
* @Date:   12-10-2016 09:10:13
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 12-10-2016 15:10:09
* @License: MIT
*/


#include "cade-window-list-element.h"
#include <data/cade-window-controller.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

struct _CadeWindowListElement {
  GtkToggleButton parent_instance;
  GtkLabel *label;
  guint winID;
  CadeWindowController *controller;
};

struct _CadeWindowListElementClass {
  GtkToggleButtonClass parent_class;
};

G_DEFINE_TYPE (CadeWindowListElement, cade_window_list_element, GTK_TYPE_TOGGLE_BUTTON)

static void cade_window_list_element_class_init (CadeWindowListElementClass *klass)
{
}

static void _cade_window_list_element_toggle(GtkToggleButton *button, gpointer data)
{
  CadeWindowListElement *self = CADE_WINDOW_LIST_ELEMENT(data);
  if(gtk_toggle_button_get_active(button))
  {
    cade_window_controller_select_window(self->controller, self->winID);
  }
}

static void cade_window_list_element_init (CadeWindowListElement *self)
{
  self->controller = cade_window_controller_new();
  g_signal_connect(self, "toggled", G_CALLBACK(_cade_window_list_element_toggle), self);
}

CadeWindowListElement *cade_window_list_element_new (gchar *title, guint winID)
{
  CadeWindowListElement *ret = g_object_new (CADE_TYPE_WINDOW_LIST_ELEMENT, "relief", GTK_RELIEF_NONE, NULL);
  cade_window_list_element_set_label(ret, title);


  GtkWidget *win = gtk_window_new(GTK_WINDOW_POPUP);
  GdkPixbuf *pb;

  GdkWindow *rw = gdk_x11_window_foreign_new_for_display(gdk_display_get_default(), winID);
  gint w, h;
  w = gdk_window_get_width(rw);
  h = gdk_window_get_height(rw);
  pb = gdk_pixbuf_get_from_window(rw, 0, 0, w, h);
  pb = gdk_pixbuf_scale_simple(pb, 300, 200, GDK_INTERP_BILINEAR);

  GtkWidget *img = gtk_image_new_from_pixbuf(pb);
  gtk_container_add(GTK_CONTAINER(win), img);
  gtk_widget_show_all(img);
  gtk_widget_set_tooltip_window(GTK_WIDGET(ret), GTK_WINDOW(win));
  gtk_widget_set_tooltip_markup(GTK_WIDGET(ret), " ");
  gtk_widget_set_has_tooltip(GTK_WIDGET(ret), TRUE);

  ret->winID = winID;
  return ret;
}

void cade_window_list_element_set_label(CadeWindowListElement *element, gchar *text)
{
  if(element->label == NULL)
  {
    element->label = GTK_LABEL(gtk_label_new(""));
    gtk_label_set_max_width_chars(element->label, 30);
    gtk_label_set_ellipsize(element->label, PANGO_ELLIPSIZE_END);
    gtk_container_add(GTK_CONTAINER(element), GTK_WIDGET(element->label));

  }
    gtk_label_set_text(element->label, text);
}

guint cade_window_list_element_get_id(CadeWindowListElement *element)
{
  return element->winID;
}
