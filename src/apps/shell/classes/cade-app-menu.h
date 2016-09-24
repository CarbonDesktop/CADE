/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   22-09-2016 15:09:62
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   mame98
* @Last modified time: 24-09-2016 11:09:88
* @License: MIT
*/



#ifndef __CADE_APP_MENU_H__
#define __CADE_APP_MENU_H__

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define CADE_TYPE_APP_MENU            (cade_app_menu_get_type ())
#define CADE_APP_MENU(o)              (G_TYPE_CHECK_INSTANCE_CAST  ((o), CADE_TYPE_APP_MENU, CadeAppMenu))
#define CADE_IS_APP_MENU(o)           (G_TYPE_CHECK_INSTANCE_TYPE  ((o), CADE_TYPE_APP_MENU))
#define CADE_APP_MENU_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CADE_TYPE_APP_MENU, CadeAppMenuClass))
#define CADE_IS_APP_MENU_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CADE_TYPE_APP_MENU))
#define CADE_APP_MENU_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CADE_TYPE_APP_MENU, CadeAppMenuClass))

typedef struct _CadeAppMenu        CadeAppMenu;
typedef struct _CadeAppMenuClass   CadeAppMenuClass;

GType        cade_app_menu_get_type (void) G_GNUC_CONST;
CadeAppMenu *cade_app_menu_new (GtkWidget *parent);
void         cade_app_menu_revert(CadeAppMenu *menu);

G_END_DECLS

#endif /* __CADE_APP_MENU_H__ */
