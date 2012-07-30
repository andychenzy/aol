
AM_CPPFLAGS = -I$(top_srcdir)/src

LDADD = $(top_srcdir)/src/.libs/libaolsys.a

AM_LDFLAGS = "-lpthread -lm -lrt"

noinst_PROGRAMS = teststring test_log

teststring_SOURCES = test_string.cc
test_log_SOURCES = test_log.cc
