/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   23-09-2016 19:09:43
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   mame98
* @Last modified time: 02-10-2016 15:10:25
* @License: MIT
*/



#ifndef __CADE_APP_ROW_H__
#define __CADE_APP_ROW_H__

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define CADE_TYPE_APP_ROW            (cade_app_row_get_type ())
#define CADE_APP_ROW(o)              (G_TYPE_CHECK_INSTANCE_CAST  ((o), CADE_TYPE_APP_ROW, CadeAppRow))
#define CADE_IS_APP_ROW(o)           (G_TYPE_CHECK_INSTANCE_TYPE  ((o), CADE_TYPE_APP_ROW))
#define CADE_APP_ROW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CADE_TYPE_APP_ROW, CadeAppRowClass))
#define CADE_IS_APP_ROW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CADE_TYPE_APP_ROW))
#define CADE_APP_ROW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CADE_TYPE_APP_ROW, CadeAppRowClass))

typedef struct _CadeAppRow        CadeAppRow;
typedef struct _CadeAppRowClass   CadeAppRowClass;

GType       cade_app_row_get_type (void) G_GNUC_CONST;
CadeAppRow *cade_app_row_new (gboolean tooltip, gchar *name, gchar *icon, gchar *description, gchar *version, gchar *exec);
gchar      *cade_app_row_get_name(CadeAppRow *row);
void        cade_app_row_make_bold(CadeAppRow *row);
void        cade_app_row_execute(CadeAppRow *row);

G_END_DECLS

#endif /* __CADE_APP_ROW_H__ */
