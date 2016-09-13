/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   13-09-2016 20:09:50
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   mame98
* @Last modified time: 13-09-2016 21:09:16
* @License: MIT
*/

#include "cade-shell-application.h"

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
  GtkWidget *test = gtk_application_window_new(GTK_APPLICATION(app));
  gtk_window_present(GTK_WINDOW(test));
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
  g_application_set_application_id(G_APPLICATION(self), "org.cade.shell");
}

CadeShellApplication *
cade_shell_application_new (void)
{
  return g_object_new (CADE_TYPE_SHELL_APPLICATION, NULL);
}
