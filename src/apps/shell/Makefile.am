bin_PROGRAMS = cade-shell

cade_shell_SOURCES = main.c
cade_shell_LDADD = ${GTK3_LIBS} ${GObject_LIBS} $(X11_LIBS)
cade_shell_LDFLAGS = -lcade-core -L=$(top_builddir)/src/lib/.libs/ -Wl,-rpath=$(top_builddir)/src/lib/.libs/
cade_shell_CFLAGS = ${GTK3_CFLAGS} ${GObject_CFLAGS} $(X11_CFLAGS) -std=c99 -I$(top_srcdir)/src/lib
