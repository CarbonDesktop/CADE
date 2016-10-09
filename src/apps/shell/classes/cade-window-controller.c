/**
* @Author: Marius Messerschmidt <marius>
* @Date:   08-10-2016 21:10:30
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 09-10-2016 13:10:80
* @License: MIT
*/

#include <config.h>
#include "cade-window-controller.h"
#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

struct _CadeWindowController {
  GObject parent_instance;
  GdkWindow *window;
};

struct _CadeWindowControllerClass {
  GObjectClass parent_class;
};

G_DEFINE_TYPE (CadeWindowController, cade_window_controller, G_TYPE_OBJECT)

static void cade_window_controller_class_init (CadeWindowControllerClass *klass)
{}

static void cade_window_controller_init (CadeWindowController *self)
{
  self->window = gdk_get_default_root_window();
}

CadeWindowController *
cade_window_controller_new ()
{
  CadeWindowController *controller = g_object_new (CADE_TYPE_WINDOW_CONTROLLER, NULL);
}

// Public methods

GList *cade_window_controller_get_all_windows(CadeWindowController *controller)
{
  Display *d = XOpenDisplay(NULL);
  Atom clientListAtom = XInternAtom(d, "_NET_CLIENT_LIST", False);
  Atom type;

  int form;             // Unused
  unsigned long len;    // Lenght of the returned list
  unsigned char *list;  // List with all X11 Windows
  unsigned long remain; // Unused


  if(Success != XGetWindowProperty(d, XDefaultRootWindow(d), clientListAtom, 0, 1024, False, XA_WINDOW, &type, &form, &len, &remain, &list))
  {
    g_warning("Could not fetch open windows from X server");
    return NULL;
  }

  g_print("len:%ld", len);

  Window *realList = (Window*) list;

  for (unsigned long x = 0; x < len; x++)
  {
    /*  Now, we have the windows and we need to fetch all the meta data
     *  and then save all this stuff into a new GObject store, connect it
     *  as a list and then return it to the request
     */
     Window w = realList[x];
     Atom nameAtom = XInternAtom(d, "_NET_WM_NAME", False);
     Atom nameType;
     char *name;               // Name of the window (title)
     int nameForm;             // Unused
     unsigned long nameLen;    // Length of the returned name
     unsigned long nameRemain; // Unused
     unsigned char *nameRaw;   // 'Raw' return location for the name


     if(Success != XGetWindowProperty(d, w, nameAtom, 0, 1024, False, AnyPropertyType, &nameType,&nameForm,&nameLen,&nameRemain,&nameRaw))
     {
        g_warning("Could not get name of window with id %ld", w);
        continue;
     }

     name = (char *) nameRaw;
     g_warning("Found %s", name);
  }
}
