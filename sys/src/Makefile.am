source_list = aol_string.cc aol_log.cc aol_config.cc

AM_LDFLAGS = "-lpthread -lm -lrt"

lib_LTLIBRARIES = libaolsys.la

libaolsys_la_SOURCES = $(source_list)
libaolsys_la_LDFLAGS = $(AM_LDFLAGS) -static-libgcc

include_HEADERS = aol_string.h aol_log.h aol_config.h

noinst_PROGRAMS=
