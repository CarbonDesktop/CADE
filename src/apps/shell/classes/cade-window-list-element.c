/**
* @Author: Marius Messerschmidt <marius>
* @Date:   12-10-2016 09:10:13
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 12-10-2016 10:10:89
* @License: MIT
*/


#include "cade-window-list-element.h"
#include <gtk/gtk.h>

struct _CadeWindowListElement {
  GtkToggleButton parent_instance;
  GtkLabel *label;
  guint winID;
};

struct _CadeWindowListElementClass {
  GtkToggleButtonClass parent_class;
};

G_DEFINE_TYPE (CadeWindowListElement, cade_window_list_element, GTK_TYPE_TOGGLE_BUTTON)

static void cade_window_list_element_class_init (CadeWindowListElementClass *klass)
{
}

static void cade_window_list_element_init (CadeWindowListElement *self)
{
}

CadeWindowListElement *cade_window_list_element_new (gchar *title, guint winID)
{
  CadeWindowListElement *ret = g_object_new (CADE_TYPE_WINDOW_LIST_ELEMENT, "relief", GTK_RELIEF_NONE, NULL);
  cade_window_list_element_set_label(ret, title);
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
