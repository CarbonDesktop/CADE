#include "cade-watch-dog.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>

struct _CadeWatchDog {
  GObject parent_instance;
  gchar *file;
  time_t last;
};

struct _CadeWatchDogClass {
  GObjectClass parent_class;
};

enum CADE_WATCH_DOG_SIGNALS
{
  CADE_WATCH_DOG_UPDATE = 0,
  CADE_WATCH_DOG_N_SIGNALS
};

static guint signals[CADE_WATCH_DOG_N_SIGNALS];
static const gint updateTimer = 1000;

G_DEFINE_TYPE (CadeWatchDog, cade_watch_dog, G_TYPE_OBJECT)

static void cade_watch_dog_class_init (CadeWatchDogClass *klass)
{
  GType params[] = {G_TYPE_STRING};
  signals[CADE_WATCH_DOG_UPDATE] = g_signal_newv("update", G_TYPE_FROM_CLASS(klass),  G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS, NULL, NULL, NULL, NULL, G_TYPE_NONE, 1, params);
}

static gboolean cade_watch_dog_trigger_update(gpointer dogData)
{
  CadeWatchDog *dog = (CadeWatchDog *)dogData;
  struct stat buffer;

  if(stat(dog->file, &buffer) != 0)
  {
    g_warning("An error occured while calling stat(%s): %s", dog->file,  strerror(errno));
    return G_SOURCE_CONTINUE;
  }

  time_t mod = mktime(gmtime(&buffer.st_mtime));

  if(mod != dog->last)
  {
    dog->last = mod;
    g_signal_emit(dog, signals[CADE_WATCH_DOG_UPDATE], 0, dog->file);
  }

  return G_SOURCE_CONTINUE;
}

static void cade_watch_dog_init (CadeWatchDog *self)
{
  g_timeout_add(updateTimer, cade_watch_dog_trigger_update, self);
}

CadeWatchDog *cade_watch_dog_new (gchar *file)
{
  CadeWatchDog *dog = g_object_new (CADE_TYPE_WATCH_DOG, NULL);
  dog->file = g_strdup(file);
  struct stat buffer;
  stat(dog->file, &buffer);
  dog->last = mktime(gmtime(&buffer.st_mtime));
  return dog;
}
