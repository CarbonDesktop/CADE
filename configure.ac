AC_INIT([CADE], [0.1.0], [https://github.com/CarbonDesktop/CADE/issues], [cade], [https://github.com/CarbonDesktop/CADE])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

AM_PROG_AR
AM_PROG_LIBTOOL

AC_LANG(C)


# General Checks
AC_PROG_CC_C99
AC_HEADER_STDC
AC_PROG_CC
AC_PROG_RANLIB

# GLib/GTK
PKG_CHECK_MODULES(GTK3, gtk+-x11-3.0 >= 3.12)
PKG_CHECK_MODULES(GLib, glib-2.0)
PKG_CHECK_MODULES(GObject, gobject-2.0)

# X Server
PKG_CHECK_MODULES(X11, x11)

# Files
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  src/lib/Makefile
  src/apps/Makefile
  src/apps/shell/Makefile
  ])


# Check for optional programs
AC_CHECK_PROGS(CPPCHECK, cppcheck)
if test -z "$CPPCHECK";
  then AC_MSG_WARN([cppcheck not found, unable to perform static code checks])
fi
AM_CONDITIONAL([HAVE_CPPCHECK], [test "$CPPCHECK" != ""])

# Done with build script
AC_OUTPUT

echo ""
echo " ========== Configuration Complete =========="
echo ""
echo "         Package:  $PACKAGE_NAME"
echo "         Version:  $PACKAGE_VERSION"
echo "      Bugtracker:  $PACKAGE_BUGREPORT"
echo "        Homepage:  $PACKAGE_URL"
echo ""
echo " To start compiling, you can use the following"
echo " three steps:"
echo ""
echo "   $ make          # Build"
echo "   $ make check    # Run all tests (optional)"
echo "   $ make install  # Install application"
echo ""
echo " ============================================"
echo ""
