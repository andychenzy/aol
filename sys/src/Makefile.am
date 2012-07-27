source_list = config.cpp

AM_LDFLAGS = "-lpthread -lm -lrt"

lib_LTLIBRARIES = libaolsys.la

libaolsys_la_SOURCES = $(source_list)
libaolsys_la_LDFLAGS = $(AM_LDFLAGS) -static-libgcc

include_HEADERS = config.h

noninst_PROGRAMS=
