/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   14-09-2016 18:09:31
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   mame98
* @Last modified time: 22-09-2016 15:09:48
* @License: MIT
*/

#include "cade-panel-window.h"
#include <gtk/gtk.h>

struct _CadePanelWindow {
  GtkApplicationWindow parent_instance;
  GdkScreen *screen;
};

struct _CadePanelWindowClass {
  GtkApplicationWindowClass parent_class;
};

G_DEFINE_TYPE (CadePanelWindow, cade_panel_window, GTK_TYPE_APPLICATION_WINDOW);

static void
cade_panel_window_class_init (CadePanelWindowClass *klass)
{
}

static void
cade_panel_window_init (CadePanelWindow *self)
{
  self->screen = gdk_screen_get_default();

  GtkWindow *win = GTK_WINDOW(self);
  gtk_window_set_decorated(win, FALSE);
  gtk_window_set_skip_taskbar_hint(win, TRUE);
  gtk_window_set_type_hint(win, GDK_WINDOW_TYPE_HINT_DOCK);
  // Position
  gtk_window_set_default_size(win, gdk_screen_get_width(self->screen), 30);
  gtk_window_move(win, 0, gdk_screen_get_height(self->screen) - 30);

  gtk_widget_realize(GTK_WIDGET(self));

  // Add struts
  GtkWidget *toplevel = gtk_widget_get_toplevel(GTK_WIDGET(self));
  GdkWindow *gdkWindow = gtk_widget_get_window(toplevel);


  long vals[4];
  vals[0] = 0;
  vals[1] = 0;
  vals[2] = 0;
  vals[3] = 30;

  GdkAtom atom = gdk_atom_intern("_NET_WM_STRUT", FALSE);
  GdkAtom card = gdk_atom_intern("CARDINAL", FALSE);

  gdk_property_change(gdkWindow, atom, card, 32, GDK_PROP_MODE_REPLACE, (guchar *)vals, 4);

}

CadePanelWindow *
cade_panel_window_new (GtkApplication *app)
{
  return g_object_new (CADE_TYPE_PANEL_WINDOW, "application" ,app ,NULL);
}
