/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   22-09-2016 15:09:62
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   mame98
* @Last modified time: 22-09-2016 21:09:15
* @License: MIT
*/



#include "cade-app-menu.h"

struct _CadeAppMenu {
  GtkWindow parent_instance;
  GtkWidget *search;
  GtkWidget *list;

  /* DATA */
  GList *categoryList;
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

GList *_build_category_list()
{
  GList *ret = NULL;
  gchar *menuItems[12][2] = { {"Audio", "applications-multimedia"}, {"Video", "applications-multimedia"}, {"Development", "applications-development"}, {"Education", "applications-science"}, {"Game", "applications-games"}, {"Graphics", "applications-graphics"}, {"Network", "applications-internet"}, {"Office", "applications-office"}, {"Science", "applications-science"}, {"Settings", "preferences-system"}, {"System", "applications-system"}, {"Utility", "applications-system"}};
  gsize n = 12;

  for(gsize x = 0; x < n; x++)
  {

    GtkWidget *row = gtk_list_box_row_new();
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_add(GTK_CONTAINER(row), box);

    GtkWidget *icon = gtk_image_new_from_icon_name(menuItems[x][1], GTK_ICON_SIZE_LARGE_TOOLBAR);
    GtkWidget *text = gtk_label_new("");

    gchar *temp = g_strdup_printf("<span size='x-large' font-weight='bold'> %s </span>", menuItems[x][0]);
    gtk_label_set_markup(GTK_LABEL(text), temp);


    gtk_box_pack_start(GTK_BOX(box), icon, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(box), text, FALSE, FALSE, 0);

    ret = g_list_append(ret, row);
    g_free(temp);
  }
  return ret;
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
  gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrollBox), 300);
  self->list = gtk_list_box_new();
  gtk_list_box_set_selection_mode(GTK_LIST_BOX(self->list), GTK_SELECTION_NONE);

  self->categoryList = _build_category_list();


  GList *iter = self->categoryList;
  while(iter != NULL)
  {
    gtk_list_box_prepend(GTK_LIST_BOX(self->list), GTK_WIDGET(iter->data));
    iter = iter->next;
  }


  GDir *dir = g_dir_open("/usr/share/applications/", 0, NULL);
  const gchar *file;

  while((file = g_dir_read_name(dir)) != NULL )
  {
    gchar *full_path = g_strdup_printf("/usr/share/applications/%s", file);
    GKeyFile *keyfile = g_key_file_new();
    g_key_file_load_from_file(keyfile, full_path, G_KEY_FILE_NONE, NULL);


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
