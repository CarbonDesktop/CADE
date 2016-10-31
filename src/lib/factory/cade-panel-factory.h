/**
* @Author: Marius Messerschmidt <marius>
* @Date:   13-10-2016 16:10:02
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 14-10-2016 20:10:27
* @License: MIT
*/


#ifndef __CADE_PANEL_FACTORY_H__
#define __CADE_PANEL_FACTORY_H__

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define CADE_TYPE_PANEL_FACTORY            (cade_panel_factory_get_type ())
#define CADE_PANEL_FACTORY(o)              (G_TYPE_CHECK_INSTANCE_CAST  ((o), CADE_TYPE_PANEL_FACTORY, CadePanelFactory))
#define CADE_IS_PANEL_FACTORY(o)           (G_TYPE_CHECK_INSTANCE_TYPE  ((o), CADE_TYPE_PANEL_FACTORY))
#define CADE_PANEL_FACTORY_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CADE_TYPE_PANEL_FACTORY, CadePanelFactoryClass))
#define CADE_IS_PANEL_FACTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CADE_TYPE_PANEL_FACTORY))
#define CADE_PANEL_FACTORY_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CADE_TYPE_PANEL_FACTORY, CadePanelFactoryClass))

typedef struct _CadePanelFactory        CadePanelFactory;
typedef struct _CadePanelFactoryClass   CadePanelFactoryClass;

GType             cade_panel_factory_get_type (void) G_GNUC_CONST;
CadePanelFactory *cade_panel_factory_new (void);
GList *cade_panel_factory_run(CadePanelFactory *factory, GtkApplication *app);
void cade_panel_factory_register(CadePanelFactory *self, gulong id, GtkWidget *(*createFunc)(void));

G_END_DECLS

#endif /* __CADE_PANEL_FACTORY_H__ */
