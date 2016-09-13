SUBDIRS = src
dist_doc_DATA = README.md AUTHORS LICENSE
BUILT_SOURCES = AUTHORS
.PHONY: AUTHORS

AUTHORS:
	echo "GIT Contributors:" > AUTHORS
	git log --format='%aN <%aE>' | sort -u >> AUTHORS

all: AUTHORS
