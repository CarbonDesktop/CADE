SUBDIRS = src
dist_doc_DATA = README.md AUTHORS LICENSE
EXTRA_DIST = scripts
BUILT_SOURCES = AUTHORS
TESTS =
DISTCLEANFILES = AUTHORS

if HAVE_CPPCHECK
TESTS += scripts/test-static.sh
endif

.PHONY: AUTHORS

AUTHORS:
	echo "GIT Contributors:" > AUTHORS
	git log --format='%aN <%aE>' | sort -u >> AUTHORS

dev-run:
	./src/apps/shell/cade-shell
