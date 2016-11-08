#include "cade-panel-spacer.h"
#include <stdlib.h>

struct _CadePanelSpacer {
  GtkLabel parent_instance;
  gint padding;
};

struct _CadePanelSpacerClass {
  GtkLabelClass parent_class;
};

G_DEFINE_TYPE (CadePanelSpacer, cade_panel_spacer, GTK_TYPE_LABEL)

static void
cade_panel_spacer_class_init (CadePanelSpacerClass *klass)
{

}

static void cade_panel_spacer_init (CadePanelSpacer *self)
{

}

static void cade_panel_spacer_set_space(CadePanelSpacer *self, gint n)
{
  gtk_widget_set_margin_start(GTK_WIDGET(self), n);
}

GtkWidget *
cade_panel_spacer_new (GHashTable *attr)
{
  CadePanelSpacer *spacer = g_object_new (CADE_TYPE_PANEL_SPACER, NULL);
  if(g_hash_table_contains(attr, "space") == FALSE)
  {
    g_critical("CadePanelSpacer is missing a 'space' attribute");
    return NULL;
  }
  cade_panel_spacer_set_space(spacer, atoi(g_hash_table_lookup(attr, "space")));
  return GTK_WIDGET(spacer);
}
