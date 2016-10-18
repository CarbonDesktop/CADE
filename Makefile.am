SUBDIRS = src
dist_doc_DATA = README.md AUTHORS LICENSE
BUILT_SOURCES = AUTHORS
dist_check_SCRIPTS = scripts/test-static.sh
TESTS =

if HAVE_CPPCHECK
TESTS += scripts/test-static.sh
endif

.PHONY: AUTHORS built-arch

AUTHORS:
	echo "GIT Contributors:" > AUTHORS
	git log --format='%aN <%aE>' | sort -u >> AUTHORS

all: AUTHORS

# Packages

build-arch:
	-rm -r build
	mkdir build -p
	cp pkgdata/arch/PKGBUILD build
	cd build && makepkg

build-deb:
	-rm -r build
	mkdir build -p
	$(MAKE) install DESTDIR="$(abs_top_srcdir)/build/"
	cp -r pkgdata/deb build/DEBIAN
	rm build/DEBIAN/*.in # Get rid of the templates
	dpkg-deb --build build
	mv build.deb @PACKAGE_TARNAME@_@PACKAGE_VERSION@.deb
