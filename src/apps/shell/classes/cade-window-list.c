/**
* @Author: Marius Messerschmidt <marius>
* @Date:   12-10-2016 09:10:48
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 12-10-2016 10:10:48
* @License: MIT
*/


#include "cade-window-list.h"
#include "cade-window-controller.h"
#include "cade-window-list-element.h"
#include "cade-app-window.h"
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
  CadeWindowList *self = CADE_WINDOW_LIST(list);

  GList *windows = cade_window_controller_get_all_windows(self->controller);
  GList *existing = gtk_container_get_children(GTK_CONTAINER(self));
  GList *existingIter;
  GList *iter = windows;

  while(iter != NULL)
  {
    CadeAppWindow *win = CADE_APP_WINDOW(iter->data);
    gchar *title = cade_app_window_get_name(win);
    guint id = cade_app_window_get_id(win);

    existingIter = existing;
    gboolean alreadyInList = FALSE;
    while(existingIter != NULL)
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
      gtk_box_pack_start(GTK_BOX(self), GTK_WIDGET(element), FALSE, FALSE, 0);
    }
    iter = iter->next;
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

CadeWindowList *
cade_window_list_new (void)
{
  return g_object_new (CADE_TYPE_WINDOW_LIST, "orientation", GTK_ORIENTATION_HORIZONTAL, NULL);
}
