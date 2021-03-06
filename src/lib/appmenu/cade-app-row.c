/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   23-09-2016 19:09:43
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 14-10-2016 20:10:40
* @License: MIT
*/



#include "cade-app-row.h"
#include <stdlib.h>
#include <string.h>

struct _CadeAppRow {
  GtkListBoxRow parent_instance;

  GtkWidget *label;

  gchar *name;
  gchar *icon;
  gchar *description;
  gchar *version;
  gchar *exec;
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
  gtk_box_pack_start(b, self->label, FALSE, FALSE, 20);

  gtk_container_add(GTK_CONTAINER(self), box);

  if(self->tooltip)
  {
    gchar *temp = g_markup_printf_escaped("<span font-weight='bold'>Name:</span> %s\n \
<span font-weight='bold'>Description:</span> %s\n \
<span font-weight='bold'>Command:</span> %s", self->name, self->description, self->exec);

    gtk_widget_set_tooltip_markup(GTK_WIDGET(self), temp);
    g_free(temp);
  }
}

CadeAppRow *
cade_app_row_new (gboolean tooltip, gchar *name, gchar *icon, gchar *description, gchar *version, gchar *exec)
{
  CadeAppRow *row = g_object_new (CADE_TYPE_APP_ROW, NULL);
  row->name = name;
  row->icon = icon;
  row->description = description;
  row->version = version;
  row->tooltip = tooltip;
  row->exec = exec;
  finalize(row);
  return row;
}

gchar *cade_app_row_get_name(CadeAppRow *row)
{
  return row->name;
}

gchar *cade_app_row_get_exec(CadeAppRow *row)
{
  return row->exec;
}

gchar *cade_app_row_get_desc(CadeAppRow *row)
{
  return row->description;
}

void cade_app_row_make_bold(CadeAppRow *row)
{
  gchar *temp = g_strdup_printf("<span size='x-large'>%s</span>", row->name);
  gtk_label_set_markup(GTK_LABEL(row->label), temp);
  g_free(temp);
}

void cade_app_row_execute(CadeAppRow *row)
{
  GRegex *regex = g_regex_new("%.", 0, 0, NULL);
  gchar *regRes = g_regex_replace(regex, row->exec, strlen(row->exec), 0, "", G_REGEX_MATCH_NOTEMPTY, NULL);
  gchar *cmd = g_strdup_printf("%s &", regRes);
  if(system(cmd) != 0)
    g_warning("Executing %s failed!", cmd);
  g_free(cmd);
  g_free(regRes);
  g_regex_unref(regex);
}
