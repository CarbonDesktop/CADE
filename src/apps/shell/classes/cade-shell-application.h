/**
* @Author: Marius Messerschmidt <mame98>
* @Date:   13-09-2016 20:09:50
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   mame98
* @Last modified time: 13-09-2016 20:09:55
* @License: MIT
*/



#ifndef __CADE_SHELL_APPLICATION_H__
#define __CADE_SHELL_APPLICATION_H__

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define CADE_TYPE_SHELL_APPLICATION            (cade_shell_application_get_type ())
#define CADE_SHELL_APPLICATION(o)              (G_TYPE_CHECK_INSTANCE_CAST  ((o), CADE_TYPE_SHELL_APPLICATION, CadeShellApplication))
#define CADE_IS_SHELL_APPLICATION(o)           (G_TYPE_CHECK_INSTANCE_TYPE  ((o), CADE_TYPE_SHELL_APPLICATION))
#define CADE_SHELL_APPLICATION_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CADE_TYPE_SHELL_APPLICATION, CadeShellApplicationClass))
#define CADE_IS_SHELL_APPLICATION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CADE_TYPE_SHELL_APPLICATION))
#define CADE_SHELL_APPLICATION_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CADE_TYPE_SHELL_APPLICATION, CadeShellApplicationClass))
#define CADE_SHELL_APPLICATION_GET_PRIVATE(o)  ((CadeShellApplicationPrivate *)((CADE_SHELL_APPLICATION (o))->priv))

typedef struct _CadeShellApplication        CadeShellApplication;
typedef struct _CadeShellApplicationClass   CadeShellApplicationClass;

GType                 cade_shell_application_get_type (void) G_GNUC_CONST;
CadeShellApplication *cade_shell_application_new (void);

G_END_DECLS

#endif /* __CADE_SHELL_APPLICATION_H__ */
