/**
* @Author: Marius Messerschmidt <marius>
* @Date:   09-10-2016 15:10:50
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 09-10-2016 16:10:73
* @License: MIT
*/

#ifndef __CADE_APP_WINDOW_H__
#define __CADE_APP_WINDOW_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define CADE_TYPE_APP_WINDOW            (cade_app_window_get_type ())
#define CADE_APP_WINDOW(o)              (G_TYPE_CHECK_INSTANCE_CAST  ((o), CADE_TYPE_APP_WINDOW, CadeAppWindow))
#define CADE_IS_APP_WINDOW(o)           (G_TYPE_CHECK_INSTANCE_TYPE  ((o), CADE_TYPE_APP_WINDOW))
#define CADE_APP_WINDOW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CADE_TYPE_APP_WINDOW, CadeAppWindowClass))
#define CADE_IS_APP_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CADE_TYPE_APP_WINDOW))
#define CADE_APP_WINDOW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CADE_TYPE_APP_WINDOW, CadeAppWindowClass))

typedef struct _CadeAppWindow        CadeAppWindow;
typedef struct _CadeAppWindowClass   CadeAppWindowClass;

GType          cade_app_window_get_type (void) G_GNUC_CONST;
CadeAppWindow * cade_app_window_new (gulong id, gchar *name);

gchar *cade_app_window_get_name(CadeAppWindow *win);
gulong cade_app_window_get_id(CadeAppWindow *win);

G_END_DECLS

#endif /* __CADE_APP_WINDOW_H__ */
