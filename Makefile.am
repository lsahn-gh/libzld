if ENABLE_TOOLS
TOOLS_DIR = tools
endif
SUBDIRS = src $(TOOLS_DIR)
DIST_SUBDIRS = src $(TOOLS_DIR)

libzld-$(API_VERSION).pc: libzld.pc
	$(AM_V_GEN)cp $< $@

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libzld-$(API_VERSION).pc

CLEANFILES = $(pkgconfig_DATA)

all-local: libzld-$(API_VERSION).pc

cleanup: distclean
	rm -rf src/*.in* tools/*.in* Makefile.in *.m4 configure configure~ build-aux autom4te.cache
