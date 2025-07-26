# rand/Makefile -- MiNTLib.
#
# This file is part of the MiNTLib project, and may only be used
# modified and distributed under the terms of the MiNTLib project
# license, COPYMINT.  By continuing to use, modify, or distribute
# this file you indicate that you have read the license and
# understand and accept it fully.

SHELL = /bin/sh

srcdir = .
top_srcdir = ..
subdir = rand

# List the C source files for this directory.
SRCS = entropy.c

SUBDIRS =

have_check = no

include $(top_srcdir)/configvars

# Make install-libs work.
LIBS =

default: all

all-here:

include $(top_srcdir)/rules $(top_srcdir)/phony

# No tests in this directory for now.
TESTS =
include $(top_srcdir)/checkrules

check-local:

install-include:

uninstall-include:

install-man:

uninstall-man:
