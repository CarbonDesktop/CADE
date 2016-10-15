/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   14-09-2016 18:09:31
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 15-10-2016 17:10:35
* @License: MIT
*/

#include "cade-panel-window.h"
#include <cade-core.h>
#include <gtk/gtk.h>

enum
{
  PROP_POSITION = 1,
  N_PROPS
};

static GParamSpec *obj_properties[N_PROPS] = { NULL, };

struct _CadePanelWindow {
  GtkApplicationWindow parent_instance;
  GdkScreen *screen;
  GtkWidget *box;

  CadeWindowController *windowController;

  gint position;
};

struct _CadePanelWindowClass {
  GtkApplicationWindowClass parent_class;
};

G_DEFINE_TYPE (CadePanelWindow, cade_panel_window, GTK_TYPE_APPLICATION_WINDOW);

static void cade_panel_window_set_property(GObject *object, guint prop_id, const GValue *val, GParamSpec *pspec)
{
  CadePanelWindow *self = CADE_PANEL_WINDOW(object);
  switch(prop_id)
  {
    case PROP_POSITION:
      self->position = g_value_get_int(val);
    break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void cade_panel_window_get_property(GObject *object, guint prop_id, GValue *val, GParamSpec *pspec)
{
  CadePanelWindow *self = CADE_PANEL_WINDOW(object);
  switch(prop_id)
  {
    case PROP_POSITION:
      g_value_set_int(val, self->position);
    break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void cade_panel_window_constructed(GObject *obj)
{
  CadePanelWindow *self = CADE_PANEL_WINDOW(obj);
  GtkWindow *win = GTK_WINDOW(self);
  long vals[4] = {0}; // This holds the strut config
  if(self->position == CADE_PANEL_POSITION_BOTTOM)
  {
    gtk_window_move(win, 0, gdk_screen_get_height(self->screen) - 30);
    vals[3] = 30;
  }
  else if(self->position == CADE_PANEL_POSITION_TOP)
  {
    gtk_window_move(win, 0, 0);
    vals[2] = 30;
  }

  gtk_widget_realize(GTK_WIDGET(self));

  // Add struts
  GtkWidget *toplevel = gtk_widget_get_toplevel(GTK_WIDGET(self));
  GdkWindow *gdkWindow = gtk_widget_get_window(toplevel);




  GdkAtom atom = gdk_atom_intern("_NET_WM_STRUT", FALSE);
  GdkAtom card = gdk_atom_intern("CARDINAL", FALSE);
  gdk_property_change(gdkWindow, atom, card, 32, GDK_PROP_MODE_REPLACE, (guchar *)vals, 4);
}

static void
cade_panel_window_class_init (CadePanelWindowClass *klass)
{
  GObjectClass *obj_class = G_OBJECT_CLASS(klass);

  obj_class->set_property = cade_panel_window_set_property;
  obj_class->get_property = cade_panel_window_get_property;
  obj_class->constructed = cade_panel_window_constructed;

  obj_properties[PROP_POSITION] = g_param_spec_int("position", "Position", "Panel Position", 0, G_MAXINT, CADE_PANEL_POSITION_BOTTOM, G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);
  g_object_class_install_properties(obj_class, N_PROPS, obj_properties);
}

static gboolean _cade_panel_window_ensure_size(gpointer data)
{
  CadePanelWindow *self = CADE_PANEL_WINDOW(data);
  gtk_window_resize(GTK_WINDOW(self), gdk_screen_get_width(self->screen), 30);
  return G_SOURCE_CONTINUE;
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

  self->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add(GTK_CONTAINER(self), self->box);

  gtk_box_pack_start(GTK_BOX(self->box), GTK_WIDGET(cade_app_menu_button_new()), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(self->box), GTK_WIDGET(cade_window_list_new()), FALSE, FALSE, 0);

  g_timeout_add(100, _cade_panel_window_ensure_size, self);

  self->windowController = cade_window_controller_new();
  cade_window_controller_get_all_windows(self->windowController);
}

CadePanelWindow *cade_panel_window_new (GtkApplication *app, enum CadePanelPosition pos)
{
  return g_object_new (CADE_TYPE_PANEL_WINDOW, "application", app, "position", pos, NULL);
}
