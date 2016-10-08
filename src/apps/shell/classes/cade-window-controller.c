/**
* @Author: Marius Messerschmidt <marius>
* @Date:   08-10-2016 21:10:30
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 08-10-2016 21:10:44
* @License: MIT
*/

#include <config.h>
#include "cade-window-controller.h"
#include <gtk/gtk.h>

struct _CadeWindowController {
  GObject parent_instance;
  GdkWindow *window;
};

struct _CadeWindowControllerClass {
  GObjectClass parent_class;
};

G_DEFINE_TYPE (CadeWindowController, cade_window_controller, G_TYPE_OBJECT)

static void cade_window_controller_class_init (CadeWindowControllerClass *klass)
{}

static void cade_window_controller_init (CadeWindowController *self)
{
  self->window = gdk_get_default_root_window();
}

CadeWindowController *
cade_window_controller_new ()
{
  CadeWindowController *controller = g_object_new (CADE_TYPE_WINDOW_CONTROLLER, NULL);
}

// Public methods

GList *cade_window_controller_get_all_windows(CadeWindowController *controller)
{
  GdkAtom prop = gdk_atom_intern("_NET_CLIENT_LIST", FALSE);

  GdkAtom type;
  gint format, length;
  guchar *data;
  gdk_property_get(controller->window, prop, GDK_NONE, 0, 1024, FALSE, &type, &format, &length, &data);
  g_warning("N: %d", length);
  for(gint x = 0; x < length; x++)
  {
    g_print("Found window with ID:%d\n", data[x]);
  }
}
