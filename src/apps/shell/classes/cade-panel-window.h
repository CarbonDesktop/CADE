/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   14-09-2016 18:09:31
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   mame98
* @Last modified time: 14-09-2016 20:09:40
* @License: MIT
*/



#ifndef __CADE_PANEL_WINDOW_H__
#define __CADE_PANEL_WINDOW_H__

#include <glib-object.h>
#include <gtk/gtk.h>

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
CadePanelWindow *cade_panel_window_new (GtkApplication *app);

G_END_DECLS

#endif /* __CADE_PANEL_WINDOW_H__ */
