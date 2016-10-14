/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   13-09-2016 20:09:50
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 14-10-2016 19:10:81
* @License: MIT
*/

#include "cade-shell-application.h"
#include "cade-panel-window.h"
#include <factory/cade-panel-factory.h>

typedef struct _CadeShellApplicationPrivate CadeShellApplicationPrivate;

struct _CadeShellApplication
{
  GtkApplication parent_instance;
  gpointer priv;
};

struct _CadeShellApplicationClass
{
  GtkApplicationClass parent_class;
};

struct _CadeShellApplicationPrivate
{
  short _placeholder;//TODO
};

G_DEFINE_TYPE (CadeShellApplication, cade_shell_application, GTK_TYPE_APPLICATION)


/* Methods */

void cade_shell_application_activate(GApplication *app)
{
  CadePanelWindow *panel = cade_panel_window_new(GTK_APPLICATION(app));

  CadePanelFactory *factory = cade_panel_factory_new();
  GList *panels = cade_panel_factory_run(factory, GTK_APPLICATION(app));
}

/* Object 'Glue' */

static void
cade_shell_application_class_init (CadeShellApplicationClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  g_type_class_add_private (klass, sizeof (CadeShellApplicationPrivate));
  GApplicationClass *parent = G_APPLICATION_CLASS(&klass->parent_class);
  parent->activate = cade_shell_application_activate;
}

static void
cade_shell_application_init (CadeShellApplication *self)
{

}

CadeShellApplication *
cade_shell_application_new (void)
{
  return g_object_new (CADE_TYPE_SHELL_APPLICATION, "application-id", "org.cade.shell", NULL);
}
