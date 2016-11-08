#ifndef __CADE_PANEL_SPACER_H__
#define __CADE_PANEL_SPACER_H__

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define CADE_TYPE_PANEL_SPACER            (cade_panel_spacer_get_type ())
#define CADE_PANEL_SPACER(o)              (G_TYPE_CHECK_INSTANCE_CAST  ((o), CADE_TYPE_PANEL_SPACER, CadePanelSpacer))
#define CADE_IS_PANEL_SPACER(o)           (G_TYPE_CHECK_INSTANCE_TYPE  ((o), CADE_TYPE_PANEL_SPACER))
#define CADE_PANEL_SPACER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CADE_TYPE_PANEL_SPACER, CadePanelSpacerClass))
#define CADE_IS_PANEL_SPACER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CADE_TYPE_PANEL_SPACER))
#define CADE_PANEL_SPACER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CADE_TYPE_PANEL_SPACER, CadePanelSpacerClass))

typedef struct _CadePanelSpacer        CadePanelSpacer;
typedef struct _CadePanelSpacerClass   CadePanelSpacerClass;

GType            cade_panel_spacer_get_type (void) G_GNUC_CONST;
GtkWidget *cade_panel_spacer_new (GHashTable *attr);

G_END_DECLS

#endif /* __CADE_PANEL_SPACER_H__ */
