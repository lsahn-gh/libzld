AM_CFLAGS = -fPIC -Wall -Wextra -Werror -pedantic -O2 -std=c11
AM_CFLAGS += -Wno-error=unused-function
AM_CFLAGS += -I. -I./include

lib_sources = \
	zl-mem.c \
	zl-object.c \
	zl-tlv-dot1ab.c

lib_headers = \
	include/zl-mem.h \
	include/zl-bind.h \
	include/zl-dlist.h \
	include/zl-macro.h \
	include/zl-object.h \
	include/zl-tlv-type.h \
	include/zl-tlv-common.h \
	include/zl-tlv-dot1ab.h

lib_LTLIBRARIES = libzld.la
libzld_la_LIBADD =
libzld_la_LDFLAGS = -version-info $(LIBZLD_API_LIBTOOL)
libzld_la_SOURCES = $(lib_sources) 
libzld_la_HEADERS = $(lib_headers)
libzld_ladir = $(includedir)/zld/zld-@API_VERSION@
