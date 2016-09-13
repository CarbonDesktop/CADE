AC_INIT([CADE], [0.0.0], [https://github.com/CarbonDesktop/CADE/issues], [cade], [https://github.com/CarbonDesktop/CADE])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

AC_LANG(C)


# General Checks
AC_PROG_CC_C99
AC_HEADER_STDC
AC_PROG_CC

# GLib/GTK
PKG_CHECK_MODULES(GTK3, gtk+-3.0 >= 3.12)
PKG_CHECK_MODULES(GLib, glib-2.0)
PKG_CHECK_MODULES(GObject, gobject-2.0)



# Files
AC_CONFIG_HEADERS([src/config.h])#
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  src/apps/Makefile
  src/apps/shell/Makefile
  ])


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
