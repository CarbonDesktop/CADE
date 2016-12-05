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
#include <windowlist/cade-window-preview.h>

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

  gtk_widget_set_tooltip_window(GTK_WIDGET(ret), GTK_WINDOW(cade_window_preview_new(winID)));
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
