#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([aol], [0.1], [andychenzy@gmail.com])
AM_INIT_AUTOMAKE(aol, 0.1, andychenzy@gmail.com)

# Checks for programs
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
AC_LANG_CPLUSPLUS
CXXFLAGS = "-g -Wall -fPIC"

if test -n "${AOL_ROOT}"; then
	ac_default_prefix = ${AOL_ROOT}
	includedir = ${ac_default_prefix}/include/aolsys
fi

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [main])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile])
AC_OUTPUT
