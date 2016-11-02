#ifndef __CADE_PANEL_LAUNCHER_H__
#define __CADE_PANEL_LAUNCHER_H__

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define CADE_TYPE_PANEL_LAUNCHER            (cade_panel_launcher_get_type ())
#define CADE_PANEL_LAUNCHER(o)              (G_TYPE_CHECK_INSTANCE_CAST  ((o), CADE_TYPE_PANEL_LAUNCHER, CadePanelLauncher))
#define CADE_IS_PANEL_LAUNCHER(o)           (G_TYPE_CHECK_INSTANCE_TYPE  ((o), CADE_TYPE_PANEL_LAUNCHER))
#define CADE_PANEL_LAUNCHER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CADE_TYPE_PANEL_LAUNCHER, CadePanelLauncherClass))
#define CADE_IS_PANEL_LAUNCHER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CADE_TYPE_PANEL_LAUNCHER))
#define CADE_PANEL_LAUNCHER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CADE_TYPE_PANEL_LAUNCHER, CadePanelLauncherClass))

typedef struct _CadePanelLauncher        CadePanelLauncher;
typedef struct _CadePanelLauncherClass   CadePanelLauncherClass;

GType              cade_panel_launcher_get_type (void) G_GNUC_CONST;
GtkWidget *cade_panel_launcher_new (GHashTable *args);

G_END_DECLS

#endif /* __CADE_PANEL_LAUNCHER_H__ */
