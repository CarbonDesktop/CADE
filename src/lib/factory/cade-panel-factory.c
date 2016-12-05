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
#include <appmenu/cade-app-menu-button.h>
#include <windowlist/cade-window-list.h>
#include <spacer/cade-panel-spacer.h>
#include <launcher/cade-panel-launcher.h>
#include <io/cade-watch-dog.h>
#include <cade-data.h>
#include <gtk/gtk.h>

struct _CadePanelFactory {
  GObject parent_instance;
  gchar *path;
  GHashTable *typeRegister;
  GtkApplication *app;
  GList *panels;
};

struct _CadePanelFactoryClass {
  GObjectClass parent_class;
};

typedef GtkWidget *(*CreateFunc)(GHashTable *);

G_DEFINE_TYPE (CadePanelFactory, cade_panel_factory, G_TYPE_OBJECT)

static gchar* getGroup(GKeyFile *keyfile, gsize n)
{
  gchar *groupname = g_strdup_printf("Item%ld", n);
  if(g_key_file_has_group(keyfile, groupname))
  {
    return groupname;
  }
  else
  {
    g_free(groupname);
    return NULL;
  }
}

CadePanelWindow *cade_panel_factory_create_panel(CadePanelFactory *factory, gchar *filePath, gboolean createWatch);

static void cade_panel_factory_handle_update(CadeWatchDog *dog, gchar *file, CadePanelFactory *factory)
{
  GList *iter = factory->panels;
  while(iter)
  {
    CadePanelWindow *win = (CadePanelWindow *) iter->data;
    if(strcmp(file, cade_panel_window_get_config_file(win)) == 0)
    {
      gtk_widget_destroy(GTK_WIDGET(win));
      factory->panels = g_list_remove(factory->panels, iter->data);
      break;
    }
    iter = iter->next;
  }


  CadePanelWindow *panel = cade_panel_factory_create_panel(factory, file, FALSE);
  if(panel != NULL)
  {
    gtk_widget_show_all(GTK_WIDGET(panel));
    gtk_window_present(GTK_WINDOW(panel));
    factory->panels = g_list_append(factory->panels, panel);
  }
}


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

  self->typeRegister = g_hash_table_new(g_direct_hash, g_direct_equal);
  cade_panel_factory_register(self, CADE_TYPE_APP_MENU_BUTTON, cade_app_menu_button_new);
  cade_panel_factory_register(self, CADE_TYPE_WINDOW_LIST, cade_window_list_new);
  cade_panel_factory_register(self, CADE_TYPE_PANEL_SPACER, cade_panel_spacer_new);
  cade_panel_factory_register(self, CADE_TYPE_PANEL_LAUNCHER, cade_panel_launcher_new);


}

CadePanelFactory *cade_panel_factory_new (void)
{
  return g_object_new (CADE_TYPE_PANEL_FACTORY, NULL);
}

CadePanelWindow *cade_panel_factory_create_panel(CadePanelFactory *factory, gchar *filePath, gboolean createWatch)
{
  GKeyFile *keyfile = g_key_file_new();
  g_key_file_load_from_file(keyfile, filePath, G_KEY_FILE_NONE, NULL);
  if(g_key_file_has_group(keyfile, "PanelConfiguration") == FALSE)
  {
    g_warning("Config file %s does not contain the section [PanelConfiguration]", filePath);
    return NULL;
  }

  if(createWatch)
  {
    CadeWatchDog *dog = cade_watch_dog_new(filePath);
    g_signal_connect(dog, "update", G_CALLBACK(cade_panel_factory_handle_update), factory);
  }

  if(g_key_file_has_key(keyfile, "PanelConfiguration", "disable", NULL))
  {
    if(g_key_file_get_boolean(keyfile, "PanelConfiguration", "disable", NULL))
    {
      g_info("Skipped!");
      g_key_file_unref(keyfile);
      return NULL;
    }
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
  CadePanelWindow *panel = cade_panel_window_new(factory->app, pos, filePath);

  gsize n = 1;
  gchar *group = NULL;

  while((group = getGroup(keyfile, n)) != NULL)
  {
    gchar *type = g_key_file_get_string(keyfile, group, "type", NULL);

    GType typeID = g_type_from_name(type);

    GtkWidget *widget = NULL;

    CreateFunc func = g_hash_table_lookup(factory->typeRegister, GSIZE_TO_POINTER(typeID));

    GHashTable *params = g_hash_table_new(g_str_hash, g_str_equal);
    gchar **keys;
    gsize nKeys;
    keys = g_key_file_get_keys(keyfile, group, &nKeys, NULL);
    for(gsize x = 0; x < nKeys; x++)
    {
      g_hash_table_insert(params, keys[x], g_key_file_get_string(keyfile, group, keys[x], NULL));
    }


    if(func == NULL)
      g_critical("Type %s (ID:%ld) not found!", type, typeID);
    else
      widget = func(params);



    cade_panel_window_add_widget(panel, widget);


    g_free(group);
    n++;
  }
  g_key_file_unref(keyfile);
  return panel;
}

GList *cade_panel_factory_run(CadePanelFactory *factory, GtkApplication *app)
{
  factory->app = app;
  factory->panels = NULL;
  GDir *panelDir = g_dir_open(factory->path, 0, NULL);
  const gchar *filename;
  while((filename = g_dir_read_name(panelDir)) != NULL)
  {
    g_info("Found panel configuration file: %s\n", filename);
    gchar *filePath = g_strdup_printf("%s%s", factory->path, filename);

    CadePanelWindow *panel = cade_panel_factory_create_panel(factory, filePath, TRUE);

    if(panel != NULL)
    {
      gtk_widget_show_all(GTK_WIDGET(panel));
      gtk_window_present(GTK_WINDOW(panel));
      factory->panels = g_list_append(factory->panels, panel);
    }

    g_free(filePath);
  }

  g_dir_close(panelDir);
  return factory->panels;
}

void cade_panel_factory_register(CadePanelFactory *self, gulong id, CreateFunc createFunc)
{
  g_hash_table_insert(self->typeRegister, GSIZE_TO_POINTER(id), createFunc);
}
