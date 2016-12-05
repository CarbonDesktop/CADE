#ifndef __CADE_WATCH_DOG_H__
#define __CADE_WATCH_DOG_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define CADE_TYPE_WATCH_DOG            (cade_watch_dog_get_type ())
#define CADE_WATCH_DOG(o)              (G_TYPE_CHECK_INSTANCE_CAST  ((o), CADE_TYPE_WATCH_DOG, CadeWatchDog))
#define CADE_IS_WATCH_DOG(o)           (G_TYPE_CHECK_INSTANCE_TYPE  ((o), CADE_TYPE_WATCH_DOG))
#define CADE_WATCH_DOG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), CADE_TYPE_WATCH_DOG, CadeWatchDogClass))
#define CADE_IS_WATCH_DOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CADE_TYPE_WATCH_DOG))
#define CADE_WATCH_DOG_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), CADE_TYPE_WATCH_DOG, CadeWatchDogClass))

typedef struct _CadeWatchDog        CadeWatchDog;
typedef struct _CadeWatchDogClass   CadeWatchDogClass;

GType         cade_watch_dog_get_type (void) G_GNUC_CONST;
CadeWatchDog *cade_watch_dog_new (gchar *file);

G_END_DECLS

#endif /* __CADE_WATCH_DOG_H__ */
