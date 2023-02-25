m4_define([api_cur], [0])
m4_define([api_rev], [0])
m4_define([api_age], [0])
m4_define([api_version], [api_cur.api_rev.api_age])

AC_INIT([libzld],
        [api_version],
        [https://github.com/memnoth/libzld/issues],
        [libzld-api_version],
        [https://github.com/memnoth/libzld])

AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([-Wall -Wportability foreign])
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
AC_PROG_CC

LT_INIT([shared disable-static])

AC_SUBST([API_MAJOR],[api_cur])
AC_SUBST([API_MINOR],[api_rev])
AC_SUBST([API_VERSION],[api_cur.api_rev])
AC_DEFINE_UNQUOTED(API_VERSION, [$API_VERSION], [API version])
#AC_SUBST([LIBZLD_API_VERSION], [api_cur.api_rev.api_age])

# API version based on libtool.
# https://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
AC_SUBST([LIBZLD_API_LIBTOOL], [api_cur:api_rev:api_age])

AC_ARG_ENABLE([tools],
  AS_HELP_STRING([--enable-tools],[build tools directory]),
  [
    case "${enableval}" in
      yes) ENABLE_TOOLS=yes ;;
      no)  ENABLE_TOOLS=no ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-tools]) ;;
    esac
  ],
  [ENABLE_TOOLS=false])
AM_CONDITIONAL(ENABLE_TOOLS, test "x$ENABLE_TOOLS" = "xyes")

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 libzld.pc])
if test "x$ENABLE_TOOLS" = "xyes"; then
  AC_CONFIG_FILES([tools/Makefile])
fi
AC_OUTPUT
