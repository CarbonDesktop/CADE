SUBDIRS = src
dist_doc_DATA = README.md AUTHORS LICENSE
BUILT_SOURCES = AUTHORS
TESTS =

if HAVE_CPPCHECK
TESTS += scripts/test-static.sh
endif

.PHONY: AUTHORS

AUTHORS:
	echo "GIT Contributors:" > AUTHORS
	git log --format='%aN <%aE>' | sort -u >> AUTHORS

all: AUTHORS
