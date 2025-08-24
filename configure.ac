m4_define([api_major], [1])
m4_define([api_minor], [0])
m4_define([api_patch], [0])
m4_define([api_version], [api_major.api_minor.api_patch])

AC_INIT([libzld],
        [api_version],
        [https://github.com/lsahn-gh/libzld/issues],
        [libzld-api_version],
        [https://github.com/lsahn-gh/libzld])

AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([-Wall -Wportability foreign])
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
AC_PROG_CC

LT_INIT([shared disable-static])

AC_SUBST([API_MAJOR],[api_major])
AC_SUBST([API_MINOR],[api_minor])
AC_SUBST([API_VERSION],[api_major.api_minor])
AC_DEFINE_UNQUOTED(API_VERSION, [$API_VERSION], [API version])

AC_SUBST([LIBZLD_API_LIBTOOL], [api_major:api_minor:api_patch])

AC_ARG_ENABLE([tests],
  AS_HELP_STRING([--enable-tests],[build tests directory]),
  [
    case "${enableval}" in
      yes) ENABLE_TESTS=yes ;;
      no)  ENABLE_TESTS=no ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-tests]) ;;
    esac
  ],
  [ENABLE_TESTS=false])
AM_CONDITIONAL(ENABLE_TESTS, test "x$ENABLE_TESTS" = "xyes")

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 libzld.pc])
if test "x$ENABLE_TESTS" = "xyes"; then
  AC_CONFIG_FILES([tests/Makefile])
fi
AC_OUTPUT
