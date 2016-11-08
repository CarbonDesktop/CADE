/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   22-09-2016 15:09:02
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 14-10-2016 19:10:15
* @License: MIT
*/



#include "cade-app-menu-button.h"
#include <appmenu/cade-app-menu.h>

struct _CadeAppMenuButton {
  GtkToggleButton parent_instance;
  CadeAppMenu *menu;
};

struct _CadeAppMenuButtonClass {
  GtkToggleButtonClass parent_class;
};

G_DEFINE_TYPE (CadeAppMenuButton, cade_app_menu_button, GTK_TYPE_TOGGLE_BUTTON)

// Callbacks

static void cade_app_menu_button_toggle(GtkToggleButton *tb)
{
  CadeAppMenuButton *self = CADE_APP_MENU_BUTTON(tb);
  if (!gtk_widget_is_visible(GTK_WIDGET(self->menu)))
  {
    cade_panel_popup_window_set_relative_to(CADE_PANEL_POPUP_WINDOW(self->menu), GTK_WIDGET(self));
    gtk_widget_show_all(GTK_WIDGET(self->menu));
    gtk_widget_set_visible(GTK_WIDGET(self->menu), TRUE);
  }
  else
  {
    gtk_widget_hide(GTK_WIDGET(self->menu));
    cade_app_menu_revert(self->menu);
  }
}

// Object


static void
cade_app_menu_button_class_init (CadeAppMenuButtonClass *klass)
{
  GTK_TOGGLE_BUTTON_CLASS(klass)->toggled = cade_app_menu_button_toggle;
}

static void
cade_app_menu_button_init (CadeAppMenuButton *self)
{
  self->menu = cade_app_menu_new(GTK_WIDGET(self));
}

GtkWidget *
cade_app_menu_button_new (GHashTable *attr)
{
  GtkWidget *icon = gtk_image_new_from_icon_name("gtk-home", GTK_ICON_SIZE_LARGE_TOOLBAR);
  CadeAppMenuButton *button = g_object_new (CADE_TYPE_APP_MENU_BUTTON, "relief", GTK_RELIEF_NONE,"image", icon,NULL);
  return GTK_WIDGET(button);
}
