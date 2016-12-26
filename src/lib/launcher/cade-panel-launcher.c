#include "cade-panel-launcher.h"
#include <stdlib.h>
#include <string.h>

struct _CadePanelLauncher {
  GtkButton parent_instance;
  gchar *exec;
};

struct _CadePanelLauncherClass {
  GtkButtonClass parent_class;
};

G_DEFINE_TYPE (CadePanelLauncher, cade_panel_launcher, GTK_TYPE_BUTTON)

static void
cade_panel_launcher_class_init (CadePanelLauncherClass *klass)
{
}

static void
cade_panel_launcher_init (CadePanelLauncher *self)
{
}

static void _clicked_launcher(GtkWidget *w, GdkEvent *e, gpointer p)
{
  CadePanelLauncher *launcher = CADE_PANEL_LAUNCHER(w);
  GRegex *regex = g_regex_new("%.", 0, 0, NULL);
  gchar *regRes = g_regex_replace(regex, launcher->exec, strlen(launcher->exec), 0, "", G_REGEX_MATCH_NOTEMPTY, NULL);
  gchar *cmd = g_strdup_printf("%s &", regRes);
  if(system(cmd) != 0)
    g_warning("Executing launcher command %s failed", cmd);
  g_free(cmd);
  g_free(regRes);
  g_regex_unref(regex);
}

void cade_panel_launcher_set_app(CadePanelLauncher *self, gchar *name)
{
  gchar *config = g_strdup_printf("%s.desktop", name);
  GKeyFile *keyfile = g_key_file_new();
  const gchar *dirs[] =  { "/usr/share/applications/", "/usr/local/share/applications/" , NULL};
  if(!g_key_file_load_from_dirs(keyfile, config, dirs , NULL, G_KEY_FILE_NONE, NULL))
  {
    g_critical("App %s not found (%s)", name, config);
    g_free(config);
    return;
  }

  gchar *appName = g_key_file_get_locale_string(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_NAME, NULL, NULL);
  gchar *icon = g_key_file_get_locale_string(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_ICON, NULL, NULL);
  self->exec = g_key_file_get_string(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_EXEC, NULL);

  gtk_widget_set_tooltip_text(GTK_WIDGET(self), appName);

  GtkWidget *image = gtk_image_new_from_icon_name(icon, GTK_ICON_SIZE_SMALL_TOOLBAR);
  gtk_button_set_image(GTK_BUTTON(self), image);

  g_free(appName);
  g_free(icon);
  g_free(config);
  g_key_file_unref(keyfile);

}

GtkWidget *
cade_panel_launcher_new (GHashTable *args)
{
  CadePanelLauncher *launcher = g_object_new (CADE_TYPE_PANEL_LAUNCHER, "relief", GTK_RELIEF_NONE, NULL);
  if(g_hash_table_contains(args, "app") == FALSE)
  {
    g_critical("CadePanelLauncher is missing the 'app' attribute");
    return NULL;
  }

  cade_panel_launcher_set_app(launcher, g_hash_table_lookup(args, "app"));
  g_signal_connect(launcher, "clicked", G_CALLBACK(_clicked_launcher), NULL);

  return GTK_WIDGET(launcher);
}
