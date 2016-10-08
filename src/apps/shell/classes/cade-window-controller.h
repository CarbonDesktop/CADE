/**
* @Author: Marius Messerschmidt <marius>
* @Date:   08-10-2016 21:10:30
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 08-10-2016 21:10:67
* @License: MIT
*/

#ifndef __CADE_WINDOW_CONTROLLER_H__
#define __CADE_WINDOW_CONTROLLER_H__

#include <glib-object.h>
#include <gdk/gdk.h>

G_BEGIN_DECLS

#define CADE_TYPE_WINDOW_CONTROLLER            (cade_window_controller_get_type ())
#define CADE_WINDOW_CONTROLLER(o)              (G_TYPE_CHECK_INSTANCE_CAST  ((o), CADE_TYPE_WINDOW_CONTROLLER, CadeWindowController))
#define CADE_IS_WINDOW_CONTROLLER(o)           (G_TYPE_CHECK_INSTANCE_TYPE  ((o), CADE_TYPE_WINDOW_CONTROLLER))
#define CADE_WINDOW_CONTROLLER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CADE_TYPE_WINDOW_CONTROLLER, CadeWindowControllerClass))
#define CADE_IS_WINDOW_CONTROLLER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CADE_TYPE_WINDOW_CONTROLLER))
#define CADE_WINDOW_CONTROLLER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CADE_TYPE_WINDOW_CONTROLLER, CadeWindowControllerClass))

typedef struct _CadeWindowController        CadeWindowController;
typedef struct _CadeWindowControllerClass   CadeWindowControllerClass;

GType                 cade_window_controller_get_type (void) G_GNUC_CONST;
CadeWindowController *cade_window_controller_new ();
GList *cade_window_controller_get_all_windows(CadeWindowController *controller);

G_END_DECLS

#endif /* __CADE_WINDOW_CONTROLLER_H__ */
