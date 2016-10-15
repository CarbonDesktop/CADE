/**
* @Author: Marius Messerschmidt <marius>
* @Date:   13-10-2016 16:10:02
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 15-10-2016 17:10:38
* @License: MIT
*/


#include "cade-panel-factory.h"
#include <string.h>
#include <core/cade-panel-window.h>
#include <cade-data.h>
#include <gtk/gtk.h>

struct _CadePanelFactory {
  GObject parent_instance;
  gchar *path;
};

struct _CadePanelFactoryClass {
  GObjectClass parent_class;
};

G_DEFINE_TYPE (CadePanelFactory, cade_panel_factory, G_TYPE_OBJECT)

static void cade_panel_factory_class_init (CadePanelFactoryClass *klass)
{
}

static void cade_panel_factory_init (CadePanelFactory *self)
{
  self->path = g_strdup_printf("%s/.config/cade/panel/", g_get_home_dir());
  if(!g_file_test(self->path, G_FILE_TEST_EXISTS | G_FILE_TEST_IS_DIR))
  {
    g_mkdir_with_parents(self->path, 0755);
    char *file = g_strdup_printf("%smain.panel", self->path);
    g_file_set_contents(file, CADE_DEFAULT_PANEL_CONFIG_FILE, strlen(CADE_DEFAULT_PANEL_CONFIG_FILE), NULL);
    g_free(file);
  }
}

CadePanelFactory *cade_panel_factory_new (void)
{
  return g_object_new (CADE_TYPE_PANEL_FACTORY, NULL);
}

GList *cade_panel_factory_run(CadePanelFactory *factory, GtkApplication *app)
{
  GList *panels = NULL;
  GDir *panelDir = g_dir_open(factory->path, 0, NULL);
  const gchar *filename;
  while((filename = g_dir_read_name(panelDir)) != NULL)
  {
    g_info("Found panel configuration file: %s\n", filename);
    gchar *filePath = g_strdup_printf("%s%s", factory->path, filename);
    GKeyFile *keyfile = g_key_file_new();
    g_key_file_load_from_file(keyfile, filePath, G_KEY_FILE_NONE, NULL);
    if(g_key_file_has_group(keyfile, "PanelConfiguration") == FALSE)
    {
      g_warning("Config file %s does not contain the section [PanelConfiguration]", filePath);
      continue;
    }

    enum CadePanelPosition pos;

    gchar *temp = g_key_file_get_string(keyfile, "PanelConfiguration", "position", NULL);
    if(g_strcmp0(temp, "top") == 0)
    {
      pos = CADE_PANEL_POSITION_TOP;
    }
    else
    {
      pos = CADE_PANEL_POSITION_BOTTOM;
    }

    CadePanelWindow *panel = cade_panel_window_new(app, pos);


    gtk_widget_show_all(GTK_WIDGET(panel));
    gtk_window_present(GTK_WINDOW(panel));
    panels = g_list_append(panels, panel);

    g_key_file_unref(keyfile);
    g_free(filePath);
  }

  g_dir_close(panelDir);
}
