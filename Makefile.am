if ENABLE_TESTS
TESTS_DIR = tests
endif
SUBDIRS = src $(TESTS_DIR)
DIST_SUBDIRS = src $(TESTS_DIR)

libzld-$(API_VERSION).pc: libzld.pc
	$(AM_V_GEN)cp $< $@

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libzld-$(API_VERSION).pc

CLEANFILES = $(pkgconfig_DATA)

all-local: libzld-$(API_VERSION).pc

cleanup: distclean
	rm -rf src/*.in* tests/*.in* Makefile.in *.m4 configure configure~ \
		   build-aux autom4te.cache $(shell find . -type d -name ".deps")
