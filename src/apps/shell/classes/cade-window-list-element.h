/**
* @Author: Marius Messerschmidt <marius>
* @Date:   12-10-2016 09:10:13
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 12-10-2016 11:10:27
* @License: MIT
*/


#ifndef __CADE_WINDOW_LIST_ELEMENT_H__
#define __CADE_WINDOW_LIST_ELEMENT_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define CADE_TYPE_WINDOW_LIST_ELEMENT            (cade_window_list_element_get_type ())
#define CADE_WINDOW_LIST_ELEMENT(o)              (G_TYPE_CHECK_INSTANCE_CAST  ((o), CADE_TYPE_WINDOW_LIST_ELEMENT, CadeWindowListElement))
#define CADE_IS_WINDOW_LIST_ELEMENT(o)           (G_TYPE_CHECK_INSTANCE_TYPE  ((o), CADE_TYPE_WINDOW_LIST_ELEMENT))
#define CADE_WINDOW_LIST_ELEMENT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CADE_TYPE_WINDOW_LIST_ELEMENT, CadeWindowListElementClass))
#define CADE_IS_WINDOW_LIST_ELEMENT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CADE_TYPE_WINDOW_LIST_ELEMENT))
#define CADE_WINDOW_LIST_ELEMENT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CADE_TYPE_WINDOW_LIST_ELEMENT, CadeWindowListElementClass))

typedef struct _CadeWindowListElement        CadeWindowListElement;
typedef struct _CadeWindowListElementClass   CadeWindowListElementClass;

GType                  cade_window_list_element_get_type (void) G_GNUC_CONST;
CadeWindowListElement *cade_window_list_element_new (gchar *title, guint winID);
void cade_window_list_element_set_label(CadeWindowListElement *element, gchar *text);
guint cade_window_list_element_get_id(CadeWindowListElement *element);

G_END_DECLS

#endif /* __CADE_WINDOW_LIST_ELEMENT_H__ */
