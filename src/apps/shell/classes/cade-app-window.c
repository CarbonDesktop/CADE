/**
* @Author: Marius Messerschmidt <marius>
* @Date:   09-10-2016 15:10:50
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 09-10-2016 16:10:85
* @License: MIT
*/

#include "cade-app-window.h"

/* Properties */

enum
{
  PROP_ID = 1,
  PROP_NAME,
  N_PROPS
};

static GParamSpec *obj_properties[N_PROPS] = { NULL, };

struct _CadeAppWindow {
  GObject parent_instance;
  gchar *name;
  gulong id;
};

struct _CadeAppWindowClass {
  GObjectClass parent_class;
};

G_DEFINE_TYPE (CadeAppWindow, cade_app_window, G_TYPE_OBJECT)

static void cade_app_window_set_property(GObject *object, guint prop_id, const GValue *val, GParamSpec *pspec)
{
  CadeAppWindow *self = CADE_APP_WINDOW(object);
  switch(prop_id)
  {
    case PROP_ID:
      self->id = g_value_get_ulong(val);
    break;

    case PROP_NAME:
      self->name = g_value_dup_string(val);
    break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void cade_app_window_get_property(GObject *object, guint prop_id, GValue *val, GParamSpec *pspec)
{
  CadeAppWindow *self = CADE_APP_WINDOW(object);
  switch(prop_id)
  {
    case PROP_ID:
      g_value_set_ulong(val, self->id);
    break;

    case PROP_NAME:
      g_value_set_string(val, self->name);
    break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}


static void cade_app_window_class_init (CadeAppWindowClass *klass)
{
  GObjectClass *obj_class = G_OBJECT_CLASS(klass);

  obj_class->set_property = cade_app_window_set_property;
  obj_class->get_property = cade_app_window_get_property;

  obj_properties[PROP_ID] = g_param_spec_ulong("windowid", "WindowID", "X Window ID", 0, G_MAXULONG, 0, G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);
  obj_properties[PROP_NAME] = g_param_spec_string("name", "Name", "Name of the Window", NULL, G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);

  g_object_class_install_properties(obj_class, N_PROPS, obj_properties);
}

static void cade_app_window_init (CadeAppWindow *self)
{
}

CadeAppWindow * cade_app_window_new (gulong id, gchar *name)
{
  return g_object_new (CADE_TYPE_APP_WINDOW, "windowid", id, "name", name, NULL);
}

gchar *cade_app_window_get_name(CadeAppWindow *win)
{
  gchar *name;
  g_object_get(G_OBJECT(win), "name", &name, NULL);
  return name;
}

gulong cade_app_window_get_id(CadeAppWindow *win)
{
  gulong id;
  g_object_get(G_OBJECT(win), "windowid", &id, NULL);
  return id;
}
