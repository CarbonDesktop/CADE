/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   22-09-2016 15:09:62
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   mame98
* @Last modified time: 24-09-2016 11:09:79
* @License: MIT
*/



#include "cade-app-menu.h"
#include "cade-app-row.h"

#include <string.h>


enum APP_MENU_MODE
{
  MODE_START = 0,
  MODE_DETAIL
};

struct _CadeAppMenu {
  GtkWindow parent_instance;
  GtkWidget *search;
  GtkWidget *list;

  GtkWidget *back;

  /* DATA */
  enum APP_MENU_MODE mode;
  GList *categoryList;
  GHashTable *categories;
};

struct _CadeAppMenuClass {
  GtkWindowClass parent_class;
};

G_DEFINE_TYPE (CadeAppMenu, cade_app_menu, GTK_TYPE_WINDOW)

static void
cade_app_menu_class_init (CadeAppMenuClass *klass)
{
}

/* 'private' */

gint _app_menu_sort_func(GtkListBoxRow *a, GtkListBoxRow *b, gpointer data)
{
  CadeAppMenu *menu = CADE_APP_MENU(data);
  if(a == NULL || b == GTK_LIST_BOX_ROW(menu->back))
  {
    return -1;
  }
  else if(b == NULL || a == GTK_LIST_BOX_ROW(menu->back))
  {
    return 1;
  }
  else
  {
    CadeAppRow *rowA = CADE_APP_ROW(a);
    CadeAppRow *rowB = CADE_APP_ROW(b);
    return strcmp(cade_app_row_get_name(rowA), cade_app_row_get_name(rowB));
  }
}

static gchar *MENU_ITEMS[12][2] = { {"Audio", "applications-multimedia"}, {"Video", "applications-multimedia"}, {"Development", "applications-development"}, {"Education", "applications-science"}, {"Game", "applications-games"}, {"Graphics", "applications-graphics"}, {"Network", "applications-internet"}, {"Office", "applications-office"}, {"Science", "applications-science"}, {"Settings", "preferences-system"}, {"System", "applications-system"}, {"Utility", "applications-system"}};

static void _build_category_list(CadeAppMenu *menu)
{
  GList *ret = NULL;

  gsize n = 12;

  menu->categories = g_hash_table_new(g_str_hash, g_str_equal);

  menu->back = GTK_WIDGET(cade_app_row_new(FALSE, "Back", "gtk-go-back", "Go back to previous page", NULL, NULL));
  cade_app_row_make_bold(CADE_APP_ROW(menu->back));

  for(gsize x = 0; x < n; x++)
  {

    GtkWidget *row = GTK_WIDGET(cade_app_row_new(FALSE, MENU_ITEMS[x][0], MENU_ITEMS[x][1], NULL, NULL, NULL));
    cade_app_row_make_bold(CADE_APP_ROW(row));
    ret = g_list_append(ret, row);

    g_hash_table_insert(menu->categories, MENU_ITEMS[x][0], NULL);
  }
  menu->categoryList = ret;
}

void _rem_entry(GtkWidget *w, gpointer data)
{
  GtkContainer *container = GTK_CONTAINER(data);
  g_object_ref(w);
  gtk_container_remove(container, w);
}

void clear_list(GtkListBox *box)
{
  gtk_container_foreach(GTK_CONTAINER(box), _rem_entry, box);
}

void app_activated (GtkListBox *box, GtkListBoxRow *row, CadeAppMenu *menu)
{
  if(row == GTK_LIST_BOX_ROW(menu->back))
  {
    clear_list(box);
    GList *iter = menu->categoryList;
    while(iter != NULL)
    {
      gtk_list_box_prepend(GTK_LIST_BOX(menu->list), GTK_WIDGET(iter->data));
      iter = iter->next;
    }
    menu->mode = MODE_START;
    return;
  }

  if(menu->mode == MODE_START)
  {
    const gchar *cat = cade_app_row_get_name(CADE_APP_ROW(row));
    GList *set = g_hash_table_lookup(menu->categories, cat);

    if(set == NULL)
      return;
    else
      menu->mode = MODE_DETAIL;

    clear_list(GTK_LIST_BOX(menu->list));
    GList *iter = set;
    while(iter != NULL)
    {
      GtkWidget *w = GTK_WIDGET(iter->data);

      gtk_list_box_prepend(GTK_LIST_BOX(menu->list), GTK_WIDGET(w));
      iter = iter->next;
    }
    gtk_list_box_prepend(GTK_LIST_BOX(menu->list), GTK_WIDGET(menu->back));
  }

  gtk_widget_show_all(GTK_WIDGET(box));
}


/* 'public' */

static void
cade_app_menu_init (CadeAppMenu *self)
{
  gtk_window_set_skip_taskbar_hint(GTK_WINDOW(self), TRUE);
  gtk_window_set_decorated(GTK_WINDOW(self), FALSE);
  gtk_container_set_border_width(GTK_CONTAINER(self), 12);

  GtkWidget *grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(self), grid);

  self->search = gtk_search_entry_new();
  gtk_grid_attach(GTK_GRID(grid), self->search, 0,2, 3, 1);

  GtkWidget *scrollBox = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scrollBox), 500);
  gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrollBox), 450);
  self->list = gtk_list_box_new();
  self->mode = MODE_START;
  g_signal_connect(self->list, "row-activated", G_CALLBACK(app_activated), self);
  gtk_list_box_set_selection_mode(GTK_LIST_BOX(self->list), GTK_SELECTION_NONE);
  gtk_list_box_set_sort_func(GTK_LIST_BOX(self->list), _app_menu_sort_func, self, NULL);

  _build_category_list(self);


  app_activated(GTK_LIST_BOX(self->list), GTK_LIST_BOX_ROW(self->back), self);



  GDir *dir = g_dir_open("/usr/share/applications/", 0, NULL);
  const gchar *file;

  while((file = g_dir_read_name(dir)) != NULL )
  {
    gchar *full_path = g_strdup_printf("/usr/share/applications/%s", file);
    GKeyFile *keyfile = g_key_file_new();
    g_key_file_load_from_file(keyfile, full_path, G_KEY_FILE_NONE, NULL);

    gchar *type = g_key_file_get_locale_string(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_TYPE, NULL, NULL);
    if(type != NULL)
    {
      if(strcmp(type, G_KEY_FILE_DESKTOP_TYPE_APPLICATION) != 0)
      {
        g_key_file_unref(keyfile);
        continue;
      }
    }

    if(g_key_file_get_boolean(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_HIDDEN, NULL))
    {
      g_key_file_unref(keyfile);
      continue;
    }

    gsize nFilter;
    gchar **onlyIn = g_key_file_get_string_list(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_ONLY_SHOW_IN, &nFilter, NULL);
    if(nFilter != 0)
    {
      g_key_file_unref(keyfile);
      continue;
    }

    gsize nCat;
    gchar **categories = g_key_file_get_string_list(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_CATEGORIES, &nCat, NULL);


    gchar *name = g_key_file_get_locale_string(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_NAME, NULL, NULL);
    gchar *icon = g_key_file_get_locale_string(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_ICON, NULL, NULL);
    gchar *description = g_key_file_get_locale_string(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_COMMENT, NULL, NULL);
    gchar *version = g_key_file_get_locale_string(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_VERSION, NULL, NULL);
    gchar *exec = g_key_file_get_locale_string(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_EXEC, NULL, NULL);

    GtkWidget *row = GTK_WIDGET(cade_app_row_new(TRUE, name, icon, description, version, exec));

    gboolean found = FALSE;
    for(gsize x = 0; x < nCat && found != TRUE ;x++)
    {
      for(gsize y = 0; y < 12; y++)
      {
        if(strcmp(MENU_ITEMS[y][0], categories[x]) == 0)
        {
          if(!found)
          {
            GList *list = g_hash_table_lookup(self->categories, categories[x]);
            list = g_list_append(list, row);
            g_hash_table_replace(self->categories, categories[x], list);
            found = TRUE;
            break;
          }
        }
      }
    }

    if(found == FALSE)
    {
      g_debug("Could not find any matching category for %s", name);
      g_object_ref_sink(row);
    }


    g_key_file_unref(keyfile);
    g_free(full_path);
  }



  gtk_container_add(GTK_CONTAINER(scrollBox), self->list);
  gtk_grid_attach(GTK_GRID(grid), scrollBox, 0, 0, 3, 2);




  gtk_widget_realize(GTK_WIDGET(self));
  gtk_window_move(GTK_WINDOW(self), 0, 1920 - gdk_window_get_height(gtk_widget_get_window(GTK_WIDGET(self)))); // TODO: DYNAMIC
}

CadeAppMenu *
cade_app_menu_new (GtkWidget *parent)
{
  return g_object_new (CADE_TYPE_APP_MENU, "type" ,GTK_WINDOW_POPUP, NULL);
}

void cade_app_menu_revert(CadeAppMenu *menu)
{
  menu->mode = MODE_START;
  app_activated(GTK_LIST_BOX(menu->list), GTK_LIST_BOX_ROW(menu->back), menu);
}
