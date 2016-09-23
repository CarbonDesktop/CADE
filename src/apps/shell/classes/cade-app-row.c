/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   23-09-2016 19:09:43
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   mame98
* @Last modified time: 23-09-2016 19:09:72
* @License: MIT
*/



#include "cade-app-row.h"

struct _CadeAppRow {
  GtkListBoxRow parent_instance;

  GtkWidget *label;

  gchar *name;
  gchar *icon;
  gchar *description;
  gchar *version;
  gboolean tooltip;
};

struct _CadeAppRowClass {
  GtkListBoxRowClass parent_class;
};

G_DEFINE_TYPE (CadeAppRow, cade_app_row, GTK_TYPE_LIST_BOX_ROW)

static void
cade_app_row_class_init (CadeAppRowClass *klass)
{
}

static void
cade_app_row_init (CadeAppRow *self)
{
}

static void finalize(CadeAppRow *self)
{
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkBox *b = GTK_BOX(box);
  gtk_box_pack_start(b, gtk_image_new_from_icon_name(self->icon, GTK_ICON_SIZE_LARGE_TOOLBAR), FALSE, FALSE, 0);

  self->label = gtk_label_new(self->name);
  gtk_box_pack_end(b, self->label, FALSE, FALSE, 0);

  gtk_container_add(GTK_CONTAINER(self), box);
}

CadeAppRow *
cade_app_row_new (gboolean tooltip, gchar *name, gchar *icon, gchar *description, gchar *version)
{
  CadeAppRow *row = g_object_new (CADE_TYPE_APP_ROW, NULL);
  row->name = name;
  row->icon = icon;
  row->description = description;
  row->version = version;
  row->tooltip = tooltip;
  finalize(row);
  return row;
}

gchar *cade_app_row_get_name(CadeAppRow *row)
{
  return row->name;
}

void cade_app_row_make_bold(CadeAppRow *row)
{
  gchar *temp = g_strdup_printf("<span size='x-large'>%s</span>", row->name);
  gtk_label_set_markup(GTK_LABEL(row->label), temp);
  g_free(temp);
}
