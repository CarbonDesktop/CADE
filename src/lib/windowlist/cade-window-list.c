/**
* @Author: Marius Messerschmidt <marius>
* @Date:   12-10-2016 09:10:48
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 13-10-2016 16:10:31
* @License: MIT
*/


#include "cade-window-list.h"
#include <data/cade-window-controller.h>
#include <windowlist/cade-window-list-element.h>
#include <windowlist/cade-app-window.h>
#include <gtk/gtk.h>

struct _CadeWindowList {
  GtkBox parent_instance;
  CadeWindowController *controller;
};

struct _CadeWindowListClass {
  GtkBoxClass parent_class;
};

G_DEFINE_TYPE (CadeWindowList, cade_window_list, GTK_TYPE_BOX)

static gboolean _cade_window_list_refresh_windows(gpointer list)
{
  if(!CADE_IS_WINDOW_LIST(list))
    return G_SOURCE_REMOVE;
  CadeWindowList *self = CADE_WINDOW_LIST(list);

  GList *windows = cade_window_controller_get_all_windows(self->controller, TRUE);
  GList *existing = gtk_container_get_children(GTK_CONTAINER(self));
  GList *existingIter;
  GList *iter = windows;

  guint activeWindow = cade_window_controller_get_active_id(self->controller);

  while(iter != NULL)
  {
    CadeAppWindow *win = CADE_APP_WINDOW(iter->data);
    gchar *title = cade_app_window_get_name(win);
    gboolean alreadyInList = FALSE;

    if(g_strcmp0(title, "cade-shell") == 0 || g_strcmp0(title, "lt-cade-shell") == 0)
      alreadyInList = TRUE;
    guint id = cade_app_window_get_id(win);

    existingIter = existing;
    while(existingIter != NULL && alreadyInList == FALSE)
    {
      guint existingID = cade_window_list_element_get_id(CADE_WINDOW_LIST_ELEMENT(existingIter->data));
      if(id == existingID)
      {
        alreadyInList = TRUE;
        break;
      }
      existingIter = existingIter->next;
    }

    if(!alreadyInList)
    {
      CadeWindowListElement *element = cade_window_list_element_new(title, id);
      gtk_box_pack_start(GTK_BOX(self), GTK_WIDGET(element), FALSE, TRUE, 0);
    }
    g_free(title);
    iter = iter->next;
  }

  existingIter = existing;
  while(existingIter != NULL)
  {
    gboolean stillThere = FALSE;
    iter = windows;

    while(iter != NULL)
    {
      guint existingID = cade_window_list_element_get_id(CADE_WINDOW_LIST_ELEMENT(existingIter->data));

      CadeAppWindow *win = CADE_APP_WINDOW(iter->data);
      guint id = cade_app_window_get_id(win);

      if(id == existingID)
      {
        stillThere = TRUE;
        gchar *title = cade_app_window_get_name(win);
        cade_window_list_element_set_label(CADE_WINDOW_LIST_ELEMENT(existingIter->data), title);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(existingIter->data), existingID == activeWindow);
        g_free(title);
        break;
      }
      iter = iter->next;
    }

    if(!stillThere)
    {
      gtk_widget_destroy(GTK_WIDGET(existingIter->data));
    }
    existingIter = existingIter->next;
  }

  gtk_widget_show_all(GTK_WIDGET(self));

  return G_SOURCE_CONTINUE;
}

static void cade_window_list_class_init (CadeWindowListClass *klass)
{
}

static void cade_window_list_init (CadeWindowList *self)
{
  self->controller = cade_window_controller_new();
  g_timeout_add(50, _cade_window_list_refresh_windows, self);
}

GtkWidget *
cade_window_list_new (GHashTable *attr)
{
  return GTK_WIDGET(g_object_new (CADE_TYPE_WINDOW_LIST, "homogeneous", TRUE, "orientation", GTK_ORIENTATION_HORIZONTAL, NULL));
}
