/**
* @Author: Marius Messerschmidt <marius>
* @Date:   08-10-2016 21:10:30
* @Email:  marius.messerschmidt@googlemail.com
* @Last modified by:   marius
* @Last modified time: 12-10-2016 15:10:69
* @License: MIT
*/

#include <config.h>
#include "cade-window-controller.h"
#include <windowlist/cade-app-window.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
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

GList *cade_window_controller_get_all_windows(CadeWindowController *controller, gboolean checkTaskbar)
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

  Window *realList = (Window*) list;
  GList *ret = NULL;
  for (unsigned long x = 0; x < len; x++)
  {
    /*  Now, we have the windows and we need to fetch all the meta data
     *  and then save all this stuff into a new GObject store, connect it
     *  as a list and then return it to the request
     */
     Window w = realList[x];

     Atom stateAtom = XInternAtom(d, "_NET_WM_STATE", False);
     Atom hiddenType;
     int hiddenForm;
     unsigned long hiddenLen, hiddenRemain;
     Atom *atomList = NULL;
     if(XGetWindowProperty(d, w, stateAtom, 0, 1024, False, XA_ATOM, &hiddenType, &hiddenForm, &hiddenLen, &hiddenRemain, (unsigned char **)&atomList))
     {
       g_warning("Could not get window states of window with id %ld", w);
       continue;
     }

     gboolean skipTaskbar = FALSE;

     for(unsigned long i = 0; i < hiddenLen; i++)
     {
       char *atomName = XGetAtomName(d, atomList[i]);

       if(strcmp(atomName, "_NET_WM_STATE_SKIP_TASKBAR") == 0)
       {
         skipTaskbar = TRUE;
         break;
       }

       XFree(atomName);
     }
     XFree(atomList);

     if(skipTaskbar && checkTaskbar)
      continue; //Window should not be displayed in taskbar

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

     /* Now, build the list with objects */
     CadeAppWindow *win = cade_app_window_new(w, name);
     ret = g_list_append(ret, win);

  }
  XCloseDisplay(d);
  return ret;
}

guint cade_window_controller_get_active_id(CadeWindowController *controller)
{
  Display *d = XOpenDisplay(NULL);
  Atom activeAtom = XInternAtom(d, "_NET_ACTIVE_WINDOW", False);
  Atom type;

  int form;             // Unused
  unsigned long len;    // length of ret;
  unsigned char *ret;   // Return for Window ID
  unsigned long remain; // Unused

  if(Success != XGetWindowProperty(d, XDefaultRootWindow(d), activeAtom, 0, 1024, False, XA_WINDOW, &type, &form, &len, &remain, &ret))
  {
    g_warning("Could not fetch active window from X-Server");
    return 0;
  }

  Window *realList = (Window*) ret;
  guint id = (Window) realList[0];


  XCloseDisplay(d);
  return id;
}

void cade_window_controller_select_window(CadeWindowController *controller, guint id)
{

  Display *d = XOpenDisplay(NULL);

  XEvent xEvent;
  xEvent.type = ClientMessage;
  xEvent.xclient.display = d;
  xEvent.xclient.window = (Window) id;
  xEvent.xclient.message_type = XInternAtom(d, "_NET_ACTIVE_WINDOW", 0);
  xEvent.xclient.format = 32;
  xEvent.xclient.data.l[0] = 2L;
  xEvent.xclient.data.l[1] = CurrentTime;
  XSendEvent(d, XDefaultRootWindow(d), 0, SubstructureNotifyMask | SubstructureRedirectMask, &xEvent);

  XCloseDisplay(d);
}

GdkPixbuf *cade_window_controller_screenshot(CadeWindowController *controller, guint id)
{
  GdkWindow *win = gdk_x11_window_foreign_new_for_display(gdk_display_get_default(), id);
  if(win == NULL)
  {
    g_critical("Could not find a window with ID=%d -> Screenshot failed", id);
    return NULL;
  }

  gint w, h;
  w = gdk_window_get_width(win);
  h = gdk_window_get_height(win);
  return gdk_pixbuf_get_from_window(win, 0, 0, w, h);
}

void cade_window_controller_close(CadeWindowController *controller, guint id)
{
  Display *d = XOpenDisplay(NULL);

  XEvent event;
  event.xclient.type = ClientMessage;
  event.xclient.window = id;
  event.xclient.message_type = XInternAtom(d, "WM_PROTOCOLS", TRUE);
  event.xclient.format = 32;
  event.xclient.data.l[0] = XInternAtom(d, "WM_DELETE_WINDOW", FALSE);
  event.xclient.data.l[1] = CurrentTime;
  XSendEvent(d, id, False, NoEventMask, &event);

  XCloseDisplay(d);
}

void cade_window_controller_maximize(CadeWindowController *controller, guint id)
{
  Display *d = XOpenDisplay(NULL);

  XEvent event;
  event.xclient.type = ClientMessage;
  event.xclient.window = id;
  event.xclient.message_type = XInternAtom(d, "_NET_WM_STATE", TRUE);
  event.xclient.format = 32;
  event.xclient.data.l[0] = 1;
  event.xclient.data.l[1] = XInternAtom(d, "_NET_WM_STATE_MAXIMIZED_VERT", FALSE);
  event.xclient.data.l[2] = XInternAtom(d, "_NET_WM_STATE_MAXIMIZED_HORZ", FALSE);
  XSendEvent(d, DefaultRootWindow(d), False, SubstructureNotifyMask, &event);

  XCloseDisplay(d);
}

void cade_window_controller_minimize(CadeWindowController *controller, guint id)
{
  Display *d = XOpenDisplay(NULL);

  XEvent event;
  event.xclient.type = ClientMessage;
  event.xclient.window = id;
  event.xclient.message_type = XInternAtom(d, "WM_CHANGE_STATE", TRUE);
  event.xclient.format = 32;
  event.xclient.data.l[0] = IconicState;
  XSendEvent(d, DefaultRootWindow(d), False, SubstructureRedirectMask|SubstructureNotifyMask, &event);

  XCloseDisplay(d);
}
