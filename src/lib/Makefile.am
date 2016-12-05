lib_LTLIBRARIES = libcade-core.la

noinst_HEADERS =         appmenu/cade-app-menu-button.h \
                         appmenu/cade-app-menu.h        \
                         appmenu/cade-app-row.h         \
                         core/cade-panel-window.h       \
                         core/cade-shell-application.h  \
                         data/cade-window-controller.h  \
                         windowlist/cade-app-window.h   \
                         windowlist/cade-window-list-element.h \
                         windowlist/cade-window-list.h  \
                         windowlist/cade-window-preview.h  \
                         factory/cade-panel-factory.h   \
                         spacer/cade-panel-spacer.h     \
                         launcher/cade-panel-launcher.h \
                         ui/cade-panel-popup-window.h   \
                         io/cade-watch-dog.h            \
                         cade-core.h                    \
                         cade-data.h



libcade_core_la_SOURCES = appmenu/cade-app-menu-button.c  \
                         appmenu/cade-app-menu.c        \
                         appmenu/cade-app-row.c         \
                         core/cade-panel-window.c       \
                         core/cade-shell-application.c  \
                         data/cade-window-controller.c  \
                         windowlist/cade-app-window.c   \
                         windowlist/cade-window-list-element.c \
                         windowlist/cade-window-list.c  \
                         windowlist/cade-window-preview.c  \
                         spacer/cade-panel-spacer.c     \
                         launcher/cade-panel-launcher.c     \
                         ui/cade-panel-popup-window.c   \
                         io/cade-watch-dog.c            \
                         factory/cade-panel-factory.c

libcade_core_la_LIBADD = ${GTK3_LIBS} ${GObject_LIBS} $(X11_LIBS)
libcade_core_la_CFLAGS = ${GTK3_CFLAGS} ${GObject_CFLAGS} $(X11_CFLAGS) -std=c99 -I$(top_srcdir)/src/lib/
