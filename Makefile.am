if ENABLE_TOOLS
TOOLS_DIR = tools
endif

SUBDIRS = src $(TOOLS_DIR)
DIST_SUBDIRS = src $(TOOLS_DIR)

cleanup: distclean
	rm -rf src/*.in* tools/*.in* *.in* *.m4 configure configure~ build-aux autom4te.cache
