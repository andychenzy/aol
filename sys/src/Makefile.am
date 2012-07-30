source_list = aol_string.cc

AM_LDFLAGS = "-lpthread -lm -lrt"

lib_LTLIBRARIES = libaolsys.la

libaolsys_la_SOURCES = $(source_list)
libaolsys_la_LDFLAGS = $(AM_LDFLAGS) -static-libgcc

include_HEADERS = aol_string.h

noinst_PROGRAMS=
