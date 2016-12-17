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

enum CONTEXT_OPTIONS {
  CONTEXT_CLOSE = 0,
  N_CONTEXT_OPTIONS
};

struct _CadeWindowListElement {
  GtkToggleButton parent_instance;
  GtkLabel *label;
  guint winID;
  CadeWindowController *controller;
  GtkWidget *contextMenu;
  GtkWidget *contextOptions[N_CONTEXT_OPTIONS];
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

static gint _cade_window_list_element_button_event(GtkWidget *w, GdkEvent *e, CadeWindowListElement *self)
{
  if (e->type == GDK_BUTTON_PRESS)
  {
    GdkEventButton *event_button = (GdkEventButton *) e;
    if (event_button->button == GDK_BUTTON_SECONDARY)
    {
      #if GTK_CHECK_VERSION(3, 22, 0)
        gtk_menu_popup_at_pointer (GTK_MENU(self->contextMenu), e);
      #else
        // TODO: This is not up to date, but we should keep it for quite some time
        gtk_menu_popup(GTK_MENU(self->contextMenu), NULL, NULL, NULL, NULL, event_button->button, event_button->time);
      #endif
    }
  }

  return FALSE;
}

static void _cade_window_list_element_context(GtkMenuItem *item, CadeWindowListElement *self)
{
  if(item ==  GTK_MENU_ITEM(self->contextOptions[CONTEXT_CLOSE]))
  {
      cade_window_controller_close(self->controller, self->winID);
  }
}

static void cade_window_list_element_init (CadeWindowListElement *self)
{
  self->controller = cade_window_controller_new();
  g_signal_connect(self, "toggled", G_CALLBACK(_cade_window_list_element_toggle), self);

  self->contextMenu = gtk_menu_new();

  self->contextOptions[CONTEXT_CLOSE] = gtk_menu_item_new_with_label("Close");
  g_signal_connect(self->contextOptions[CONTEXT_CLOSE], "activate", G_CALLBACK(_cade_window_list_element_context), self);

  gtk_menu_shell_append(GTK_MENU_SHELL(self->contextMenu), self->contextOptions[CONTEXT_CLOSE]);

  gtk_widget_show_all(GTK_WIDGET(self->contextMenu));

  g_signal_connect(self, "button_press_event", G_CALLBACK(_cade_window_list_element_button_event), self);
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
