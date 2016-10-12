/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   22-09-2016 15:09:02
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 12-10-2016 09:10:90
* @License: MIT
*/



#ifndef __CADE_APP_MENU_BUTTON_H__
#define __CADE_APP_MENU_BUTTON_H__

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define CADE_TYPE_APP_MENU_BUTTON            (cade_app_menu_button_get_type ())
#define CADE_APP_MENU_BUTTON(o)              (G_TYPE_CHECK_INSTANCE_CAST  ((o), CADE_TYPE_APP_MENU_BUTTON, CadeAppMenuButton))
#define CADE_IS_APP_MENU_BUTTON(o)           (G_TYPE_CHECK_INSTANCE_TYPE  ((o), CADE_TYPE_APP_MENU_BUTTON))
#define CADE_APP_MENU_BUTTON_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CADE_TYPE_APP_MENU_BUTTON, CadeAppMenuButtonClass))
#define CADE_IS_APP_MENU_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CADE_TYPE_APP_MENU_BUTTON))
#define CADE_APP_MENU_BUTTON_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CADE_TYPE_APP_MENU_BUTTON, CadeAppMenuButtonClass))

typedef struct _CadeAppMenuButton        CadeAppMenuButton;
typedef struct _CadeAppMenuButtonClass   CadeAppMenuButtonClass;

GType              cade_app_menu_button_get_type (void) G_GNUC_CONST;
CadeAppMenuButton *cade_app_menu_button_new (void);

G_END_DECLS

#endif /* __CADE_APP_MENU_BUTTON_H__ */
