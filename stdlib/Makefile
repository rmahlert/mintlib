# stdlib/Makefile -- MiNTLib.
# Copyright (C) 2000 Guido Flohr <guido@freemint.de>
#
# This file is part of the MiNTLib project, and may only be used
# modified and distributed under the terms of the MiNTLib project
# license, COPYMINT.  By continuing to use, modify, or distribute
# this file you indicate that you have read the license and
# understand and accept it fully.

SHELL = /bin/sh

srcdir = .
top_srcdir = ..
subdir = stdlib

# Add all C source files for the library here.
# This includes the existing stdlib functions plus our new file.
SRCS = abort.c abs.c atexit.c atoi.c atol.c atof.c bsearch.c calloc.c \
       div.c getenv.c labs.c ldiv.c malloc.c mblen.c mbstowcs.c \
       mbtowc.c putenv.c qsort.c rand.c realloc.c strtod.c strtol.c \
       strtoul.c system.c wcstombs.c wctomb.c arc4random_buf.c

SUBDIRS =

have_check = yes

include $(top_srcdir)/configvars

# Make install-libs work.
LIBS =

default: all

all-here:

include $(top_srcdir)/rules $(top_srcdir)/phony

# NOTE: The test "cc" should come first!
TESTS = cc canon canon2 div mb rand sort strtod strtol
EXTRAPRGS = ftest dtest
include $(top_srcdir)/checkrules

CFLAGS-test-cc.c = -ffloat-store
CFLAGS-test-strtod.c = -ffloat-store

check-local:

install-include:

uninstall-include:

install-man:

uninstall-man:
