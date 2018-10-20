#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.


AC_PREREQ([2.69])
AC_INIT([hackertyper], [1.0], [])
AM_INIT_AUTOMAKE

default_programdata="data/kernel.txt"


AC_ARG_WITH([programdata],
        AS_HELP_STRING([--with-programdata],[Set which data file hackertyper outputs from])
)
AC_MSG_NOTICE([$with_programdata])
AS_IF([test "x$with_programdata" != "x"],
      [AC_SUBST([program_data],[`realpath $with_programdata`])],
      [AC_SUBST([program_data],[`realpath $default_programdata`])]
)


AC_CONFIG_SRCDIR([src/hackertyper.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([strtol])

AC_CONFIG_FILES([Makefile
                 data/Makefile
                 man/Makefile
                 src/Makefile])
AC_OUTPUT
