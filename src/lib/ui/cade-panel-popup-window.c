#include "cade-panel-popup-window.h"

struct _CadePanelPopupWindow {
  GtkWindow parent_instance;
};

struct _CadePanelPopupWindowClass {
  GtkWindowClass parent_class;
};

G_DEFINE_TYPE (CadePanelPopupWindow, cade_panel_popup_window, GTK_TYPE_WINDOW)

static void
cade_panel_popup_window_class_init (CadePanelPopupWindowClass *klass)
{
}

static void
cade_panel_popup_window_init (CadePanelPopupWindow *self)
{
}

CadePanelPopupWindow *
cade_panel_popup_window_new (void)
{
  return g_object_new (CADE_TYPE_PANEL_POPUP_WINDOW, NULL);
}

void cade_panel_popup_window_set_relative_to(CadePanelPopupWindow *menu, GtkWidget *relative)
{
  gtk_widget_realize(GTK_WIDGET(menu));
  gtk_widget_show_all(GTK_WIDGET(menu));
  GdkWindow *relativeWindow = gtk_widget_get_window(relative);
  if(relativeWindow == NULL)
  {
    gtk_widget_realize(GTK_WIDGET(relative));
    relativeWindow = gtk_widget_get_window(relative);
  }
  gint x = 0, y = 0;
  gdk_window_get_position(relativeWindow, &x, &y);

  gint height = 0, width = 0;
  gtk_window_get_size(GTK_WINDOW(menu), &width, &height);
  y -= height;

  if(y < 0)
  {
    gdk_window_get_position(relativeWindow, &x, &y);
    y += gdk_window_get_height(relativeWindow);
  }
  gtk_window_move(GTK_WINDOW(menu), x, y);
}
