#ifndef __CADE_WINDOW_LIST_H__
#define __CADE_WINDOW_LIST_H__

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define CADE_TYPE_WINDOW_LIST            (cade_window_list_get_type ())
#define CADE_WINDOW_LIST(o)              (G_TYPE_CHECK_INSTANCE_CAST  ((o), CADE_TYPE_WINDOW_LIST, CadeWindowList))
#define CADE_IS_WINDOW_LIST(o)           (G_TYPE_CHECK_INSTANCE_TYPE  ((o), CADE_TYPE_WINDOW_LIST))
#define CADE_WINDOW_LIST_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CADE_TYPE_WINDOW_LIST, CadeWindowListClass))
#define CADE_IS_WINDOW_LIST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CADE_TYPE_WINDOW_LIST))
#define CADE_WINDOW_LIST_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CADE_TYPE_WINDOW_LIST, CadeWindowListClass))

typedef struct _CadeWindowList        CadeWindowList;
typedef struct _CadeWindowListClass   CadeWindowListClass;

GType           cade_window_list_get_type (void) G_GNUC_CONST;
GtkWidget       *cade_window_list_new (GHashTable *attr);
G_END_DECLS

#endif /* __CADE_WINDOW_LIST_H__ */
