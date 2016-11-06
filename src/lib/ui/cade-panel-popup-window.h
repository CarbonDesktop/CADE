#ifndef __CADE_PANEL_POPUP_WINDOW_H__
#define __CADE_PANEL_POPUP_WINDOW_H__

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define CADE_TYPE_PANEL_POPUP_WINDOW            (cade_panel_popup_window_get_type ())
#define CADE_PANEL_POPUP_WINDOW(o)              (G_TYPE_CHECK_INSTANCE_CAST  ((o), CADE_TYPE_PANEL_POPUP_WINDOW, CadePanelPopupWindow))
#define CADE_IS_PANEL_POPUP_WINDOW(o)           (G_TYPE_CHECK_INSTANCE_TYPE  ((o), CADE_TYPE_PANEL_POPUP_WINDOW))
#define CADE_PANEL_POPUP_WINDOW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CADE_TYPE_PANEL_POPUP_WINDOW, CadePanelPopupWindowClass))
#define CADE_IS_PANEL_POPUP_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CADE_TYPE_PANEL_POPUP_WINDOW))
#define CADE_PANEL_POPUP_WINDOW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CADE_TYPE_PANEL_POPUP_WINDOW, CadePanelPopupWindowClass))

typedef struct _CadePanelPopupWindow        CadePanelPopupWindow;
typedef struct _CadePanelPopupWindowClass   CadePanelPopupWindowClass;

GType                 cade_panel_popup_window_get_type (void) G_GNUC_CONST;
CadePanelPopupWindow *cade_panel_popup_window_new (void);
void cade_panel_popup_window_set_relative_to(CadePanelPopupWindow *menu, GtkWidget *relative);

G_END_DECLS

#endif /* __CADE_PANEL_POPUP_WINDOW_H__ */
