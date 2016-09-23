/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   22-09-2016 15:09:62
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   mame98
* @Last modified time: 23-09-2016 17:09:82
* @License: MIT
*/



#include "cade-app-menu.h"

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

static const gchar *_row_get_text(GtkListBoxRow *row)
{
  GtkWidget *box = gtk_bin_get_child(GTK_BIN(row));
  GList *elements = gtk_container_get_children(GTK_CONTAINER(box));
  return gtk_label_get_text(GTK_LABEL(elements->next->data));
}

gint _app_menu_sort_func(GtkListBoxRow *a, GtkListBoxRow *b, gpointer data)
{
  CadeAppMenu *menu = CADE_APP_MENU(data);
  if(a == NULL || b == GTK_LIST_BOX_ROW(menu->back))
    return -1;
  else if(b == NULL || a == GTK_LIST_BOX_ROW(menu->back))
    return 1;
  else
    return strcmp(_row_get_text(a), _row_get_text(b));
}

static GtkWidget *_app_entry_new(gchar *name, gchar *icon)
{
  GtkWidget *ret = gtk_list_box_row_new();
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_container_add(GTK_CONTAINER(ret), box);

  gtk_box_pack_start(GTK_BOX(box), gtk_image_new_from_icon_name(icon, GTK_ICON_SIZE_LARGE_TOOLBAR), FALSE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(box), gtk_label_new(name), FALSE, FALSE, 0);

  return ret;
}

static gchar *MENU_ITEMS[12][2] = { {"Audio", "applications-multimedia"}, {"Video", "applications-multimedia"}, {"Development", "applications-development"}, {"Education", "applications-science"}, {"Game", "applications-games"}, {"Graphics", "applications-graphics"}, {"Network", "applications-internet"}, {"Office", "applications-office"}, {"Science", "applications-science"}, {"Settings", "preferences-system"}, {"System", "applications-system"}, {"Utility", "applications-system"}};

static void _build_category_list(CadeAppMenu *menu)
{
  GList *ret = NULL;

  gsize n = 12;

  menu->categories = g_hash_table_new(g_str_hash, g_str_equal);

  menu->back = gtk_list_box_row_new();
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_container_add(GTK_CONTAINER(menu->back), box);
  gtk_box_pack_end(GTK_BOX(box), gtk_label_new("<< back"), FALSE, FALSE, 0);


  for(gsize x = 0; x < n; x++)
  {

    GtkWidget *row = gtk_list_box_row_new();
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_add(GTK_CONTAINER(row), box);

    GtkWidget *icon = gtk_image_new_from_icon_name(MENU_ITEMS[x][1], GTK_ICON_SIZE_LARGE_TOOLBAR);
    GtkWidget *text = gtk_label_new("");

    gchar *temp = g_strdup_printf("<span size='x-large' font-weight='bold'>%s</span>", MENU_ITEMS[x][0]);
    gtk_label_set_markup(GTK_LABEL(text), temp);


    gtk_box_pack_start(GTK_BOX(box), icon, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(box), text, FALSE, FALSE, 0);

    ret = g_list_append(ret, row);
    g_free(temp);

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
    const gchar *cat = _row_get_text(row);
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

    gsize nCat;
    gchar **categories = g_key_file_get_string_list(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_CATEGORIES, &nCat, NULL);


    gchar *name = g_key_file_get_locale_string(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_NAME, NULL, NULL);
    gchar *icon = g_key_file_get_locale_string(keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_ICON, NULL, NULL);
    GtkWidget *row = _app_entry_new(name, icon);

    gboolean found = FALSE;
    for(gsize x = 0; x < nCat && found != TRUE ;x++)
    {
      for(gsize y = 0; y < 12; y++)
      {
        if(strcmp(MENU_ITEMS[y][0], categories[x]) == 0)
        {
          GList *list = g_hash_table_lookup(self->categories, categories[x]);
          list = g_list_append(list, row);
          g_hash_table_replace(self->categories, categories[x], list);
          found = TRUE;
          break;
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
