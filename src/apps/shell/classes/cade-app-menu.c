/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   22-09-2016 15:09:62
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   mame98
* @Last modified time: 22-09-2016 16:09:01
* @License: MIT
*/



#include "cade-app-menu.h"

struct _CadeAppMenu {
  GtkWindow parent_instance;
};

struct _CadeAppMenuClass {
  GtkWindowClass parent_class;
};

G_DEFINE_TYPE (CadeAppMenu, cade_app_menu, GTK_TYPE_WINDOW)

static void
cade_app_menu_class_init (CadeAppMenuClass *klass)
{
}

static void
cade_app_menu_init (CadeAppMenu *self)
{

  gtk_window_set_decorated(GTK_WINDOW(self), FALSE);
  gtk_container_set_border_width(GTK_CONTAINER(self), 12);
  gtk_container_add(self, gtk_label_new("HEY"));

  gtk_widget_realize(GTK_WIDGET(self));
  gtk_window_move(GTK_WINDOW(self), 0, 1920 - gdk_window_get_height(gtk_widget_get_window(GTK_WIDGET(self)))); // TODO: DYNAMIC
}

CadeAppMenu *
cade_app_menu_new (GtkWidget *parent)
{
  return g_object_new (CADE_TYPE_APP_MENU, "type" ,GTK_WINDOW_POPUP, "attached-to", parent, NULL);
}
