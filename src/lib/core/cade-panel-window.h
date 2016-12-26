/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   14-09-2016 18:09:31
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 15-10-2016 17:10:29
* @License: MIT
*/



#ifndef __CADE_PANEL_WINDOW_H__
#define __CADE_PANEL_WINDOW_H__

#include <glib-object.h>
#include <gtk/gtk.h>

enum CadePanelPosition
{
  CADE_PANEL_POSITION_BOTTOM = 0,
  CADE_PANEL_POSITION_TOP
};

G_BEGIN_DECLS

#define CADE_TYPE_PANEL_WINDOW            (cade_panel_window_get_type ())
#define CADE_PANEL_WINDOW(o)              (G_TYPE_CHECK_INSTANCE_CAST  ((o), CADE_TYPE_PANEL_WINDOW, CadePanelWindow))
#define CADE_IS_PANEL_WINDOW(o)           (G_TYPE_CHECK_INSTANCE_TYPE  ((o), CADE_TYPE_PANEL_WINDOW))
#define CADE_PANEL_WINDOW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CADE_TYPE_PANEL_WINDOW, CadePanelWindowClass))
#define CADE_IS_PANEL_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CADE_TYPE_PANEL_WINDOW))
#define CADE_PANEL_WINDOW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CADE_TYPE_PANEL_WINDOW, CadePanelWindowClass))

typedef struct _CadePanelWindow        CadePanelWindow;
typedef struct _CadePanelWindowClass   CadePanelWindowClass;

GType            cade_panel_window_get_type (void) G_GNUC_CONST;
CadePanelWindow *cade_panel_window_new (GtkApplication *app, enum CadePanelPosition pos, gchar *file);
void cade_panel_window_add_widget(CadePanelWindow *panel, GtkWidget *widget, gchar *pull);
gchar *cade_panel_window_get_config_file(CadePanelWindow *win);

G_END_DECLS

#endif /* __CADE_PANEL_WINDOW_H__ */
