AC_INIT(gnome-commander, 1.5.0, http://bugzilla.gnome.org/enter_bug.cgi?product=gnome-commander)
AC_CONFIG_SRCDIR(src/gnome-cmd-includes.h)
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE

GNOME_DOC_INIT

AM_MAINTAINER_MODE
AM_CONFIG_HEADER(config.h)

AC_GNU_SOURCE

AC_PROG_CC
AC_PROG_CXX
AM_PROG_LEX
AM_PROG_LIBTOOL
IT_PROG_INTLTOOL([0.35.0])

dnl make sure we keep ACLOCAL_FLAGS around for maintainer builds to work
AC_SUBST(ACLOCAL_AMFLAGS, "$ACLOCAL_FLAGS -I m4")

AX_CXX_COMPILE_STDCXX_11

dnl add -Wall to CFLAGS when using gcc
CC_WARNINGS=
if test "x$GCC" = "xyes"; then
  CC_WARNINGS="-Wall"
fi
AC_SUBST(CC_WARNINGS)

dnl ===================
dnl Gettext stuff
dnl ===================

GETTEXT_PACKAGE=gnome-commander
AC_SUBST(GETTEXT_PACKAGE)
AM_GLIB_GNU_GETTEXT


dnl ===================
dnl Check for libraries
dnl ===================

GLIB_REQ=2.6.0
GMODULE_REQ=2.0.0
GTK_REQ=2.8.0
GNOME_REQ=2.0.0
GNOMEUI_REQ=2.4.0
GNOMEVFS_REQ=2.0.0
GNOME_KEYRING_REQ=2.22
UNIQUE_REQ=0.9.3
PYTHON_REQ=2.5
EXIV2_REQ=0.14
TAGLIB_REQ=1.4
LIBGSF_REQ=1.12.0
POPPLER_REQ=0.18

AC_SUBST(GLIB_REQ)
AC_SUBST(GTK_REQ)
AC_SUBST(GNOME_REQ)
AC_SUBST(GNOMEUI_REQ)
AC_SUBST(GNOMEVFS_REQ)
AC_SUBST(GNOME_KEYRING_REQ)
AC_SUBST(UNIQUE_REQ)
AC_SUBST(PYTHON_REQ)
AC_SUBST(EXIV2_REQ)
AC_SUBST(TAGLIB_REQ)
AC_SUBST(LIBGSF_REQ)
AC_SUBST(POPPLER_REQ)
AC_SUBST(GOBJECT_CFLAGS)

dnl Check for glib
AC_MSG_CHECKING(if glib >= ${GLIB_REQ} exists)
if pkg-config --exists glib-2.0 ; then
    GLIB_CFLAGS=`pkg-config --cflags glib-2.0`
    GLIB_LIBS=`pkg-config --libs glib-2.0`
    GLIB_PREFIX=`pkg-config --variable=prefix glib-2.0`
    GLIB_VERSION=`pkg-config --modversion glib-2.0`
    AC_SUBST(GLIB_VERSION)
    AC_SUBST(GLIB_PREFIX)
    AC_SUBST(GLIB_CFLAGS)
    AC_SUBST(GLIB_LIBS)

    if pkg-config --exists glib-2.0 '>=' ${GLIB_REQ} ; then
        AC_MSG_RESULT(yes)
    else
        AC_MSG_ERROR("only ${GLIB_VERSION} found")
    fi
else
    AC_MSG_ERROR(no)
fi

dnl Check for gobject
PKG_CHECK_MODULES([GOBJECT],[gobject-2.0])

dnl Check for gmodule
AC_MSG_CHECKING(if gmodule >= ${GMODULE_REQ} exists)
if pkg-config --exists gmodule-2.0 ; then
    if pkg-config --exists gmodule-2.0 '>=' ${GMODULE_REQ} ; then
        AC_MSG_RESULT(yes)
        GMODULE_AVAIL="yes"
    else
        AC_MSG_ERROR("only `pkg-config --modversion gmodule-2.0` found")
        GMODULE_AVAIL="no"
    fi
else
    AC_MSG_ERROR(no)
    GMODULE_AVAIL="no"
fi
AC_SUBST(GMODULE_AVAIL)


dnl Check for gtk+
AC_MSG_CHECKING(if gtk+ >= ${GTK_REQ} exists)
if pkg-config --exists gtk+-2.0 ; then
    GTK_CFLAGS=`pkg-config --cflags gtk+-2.0`
    GTK_LIBS=`pkg-config --libs gtk+-2.0`
    GTK_PREFIX=`pkg-config --variable=prefix gtk+-2.0`
    GTK_VERSION=`pkg-config --modversion gtk+-2.0`
    AC_SUBST(GTK_VERSION)
    AC_SUBST(GTK_PREFIX)
    AC_SUBST(GTK_CFLAGS)
    AC_SUBST(GTK_LIBS)

    if pkg-config --exists gtk+-2.0 '>=' ${GTK_REQ} ; then
        AC_MSG_RESULT(yes)
    else
        AC_MSG_ERROR("only ${GTK_VERSION} found")
    fi
else
    AC_MSG_ERROR(no)
fi


dnl Check for libgnome
AC_MSG_CHECKING(if libgnome >= ${GNOME_REQ} exists)
if pkg-config --exists libgnome-2.0 ; then
    GNOME_CFLAGS=`pkg-config --cflags libgnome-2.0`
    GNOME_LIBS=`pkg-config --libs libgnome-2.0`
    GNOME_PREFIX=`pkg-config --variable=prefix libgnome-2.0`
    GNOME_VERSION=`pkg-config --modversion libgnome-2.0`
    AC_SUBST(GNOME_VERSION)
    AC_SUBST(GNOME_PREFIX)
    AC_SUBST(GNOME_LIBS)
    AC_SUBST(GNOME_CFLAGS)

    if pkg-config --exists libgnome-2.0 '>=' ${GNOME_REQ} ; then
        AC_MSG_RESULT(yes)
    else
        AC_MSG_ERROR("only ${GNOME_VERSION} found")
    fi
else
    AC_MSG_ERROR(no)
fi


dnl Check for libgnomeui
AC_MSG_CHECKING(if libgnomeui >= ${GNOMEUI_REQ} exists)
if pkg-config --exists libgnomeui-2.0 ; then
    GNOMEUI_CFLAGS=`pkg-config --cflags libgnomeui-2.0`
    GNOMEUI_LIBS=`pkg-config --libs libgnomeui-2.0`
    GNOMEUI_PREFIX=`pkg-config --variable=prefix libgnomeui-2.0`
    GNOMEUI_VERSION=`pkg-config --modversion libgnomeui-2.0`
    AC_SUBST(GNOMEUI_VERSION)
    AC_SUBST(GNOMEUI_PREFIX)
    AC_SUBST(GNOMEUI_CFLAGS)
    AC_SUBST(GNOMEUI_LIBS)

    if pkg-config --exists libgnomeui-2.0 '>=' ${GNOMEUI_REQ} ; then
        AC_MSG_RESULT(yes)
    else
        AC_MSG_ERROR("only ${GNOMEUI_VERSION} found")
    fi
else
    AC_MSG_ERROR(no)
fi


dnl Check for gnome-vfs
AC_MSG_CHECKING(if gnome-vfs >= ${GNOMEVFS_REQ} exists)
if pkg-config --exists gnome-vfs-2.0 ; then
    GNOMEVFS_CFLAGS=`pkg-config --cflags gnome-vfs-2.0`
    GNOMEVFS_LIBS=`pkg-config --libs gnome-vfs-2.0`
    GNOMEVFS_PREFIX=`pkg-config --variable=prefix gnome-vfs-2.0`
    GNOMEVFS_VERSION=`pkg-config --modversion gnome-vfs-2.0`
    AC_SUBST(GNOMEVFS_VERSION)
    AC_SUBST(GNOMEVFS_PREFIX)
    AC_SUBST(GNOMEVFS_CFLAGS)
    AC_SUBST(GNOMEVFS_LIBS)

    if pkg-config --exists gnome-vfs-2.0 '>=' ${GNOMEVFS_REQ} ; then
        have_gnomevfs=yes
        AC_MSG_RESULT(yes)
    else
	have_gnomevfs=no
        AC_MSG_ERROR("only ${GNOMEVFS_VERSION} found")
    fi
else
    have_gnomevfs=no
    AC_MSG_ERROR(no)
fi


dnl Check for gnome-keyring
PKG_CHECK_MODULES(GNOME_KEYRING, [ gnome-keyring-1 >= ${GNOME_KEYRING_REQ} ])
GNOME_KEYRING_PREFIX=`pkg-config --variable=prefix gnome-keyring-1`
GNOME_KEYRING_VERSION=`pkg-config --modversion gnome-keyring-1`
AC_SUBST([GNOME_KEYRING_PREFIX])
AC_SUBST([GNOME_KEYRING_VERSION])


dnl Check for libUnique
PKG_CHECK_MODULES(UNIQUE, [ unique-1.0 >= ${UNIQUE_REQ} ])
UNIQUE_PREFIX=`pkg-config --variable=prefix unique-1.0`
UNIQUE_VERSION=`pkg-config --modversion unique-1.0`
AC_SUBST([UNIQUE_PREFIX])
AC_SUBST([UNIQUE_VERSION])


dnl Check for samba support
AC_ARG_WITH(samba, [  --without-samba         disable SAMBA support])
have_samba=no
if test "x$with_samba" != xno; then
   if test "x$have_gnomevfs" != xyes; then
   have_samba=no
   else
   have_samba=yes
   fi
fi
if test "x$have_samba" = "xyes"; then
   AC_DEFINE(HAVE_SAMBA, 1, [Define to 1 if you have SAMBA support])
fi
AM_CONDITIONAL([HAVE_SAMBA],[test "x$have_samba" = "xyes"])


dnl Check for exiv2 support
AC_ARG_WITH(exiv2, [  --without-exiv2         disable EXIF and IPTC support])
have_exiv2=no
if test x$with_exiv2 != xno; then
    PKG_CHECK_MODULES(EXIV2, exiv2 >= $EXIV2_REQ, have_exiv2=yes, have_exiv2=no)
fi
if test "x$have_exiv2" = "xyes"; then
   AC_DEFINE(HAVE_EXIV2, 1, [Define to 1 if you have EXIF and IPTC support])
fi


dnl Check for taglib support
AC_ARG_WITH(taglib, [  --without-taglib         disable taglib (ID3, Vorbis, APE and FLAC) support])
have_taglib=no
if test x$with_taglib != xno; then
    PKG_CHECK_MODULES(TAGLIB, taglib >= $TAGLIB_REQ, have_taglib=yes, have_taglib=no)
fi
if test "x$have_taglib" = "xyes"; then
   AC_DEFINE(HAVE_ID3, 1, [Define to 1 if you have taglib (ID3, Vorbis, APE and FLAC) support])
fi


dnl Check for libchm support
AC_ARG_WITH(libchm, [  --without-libchm         disable CHM support])
have_chm=no
AC_CHECK_LIB(chm, chm_open, have_chm=yes, have_chm=no)
AM_CONDITIONAL(HAVE_CHM, test "x$have_chm" = "xyes")


dnl Check for libgsf support
AC_ARG_WITH(libgsf, [  --without-libgsf         disable OLE and ODF support])
have_gsf=no
if test x$with_libgsf != xno; then
    PKG_CHECK_MODULES(GSF, libgsf-1 >= $LIBGSF_REQ, have_gsf=yes, have_gsf=no)
fi
if test "x$have_gsf" = "xyes"; then
    PKG_CHECK_MODULES(GSF_1_14_26, libgsf-1 >= 1.14.26,
		      AC_DEFINE(HAVE_GSF_1_14_26,1,[Define to 1 if you have libgsf >= 1.14.26]),
		      have_gsf_1_14_26=no)
fi
if test "x$have_gsf" = "xyes"; then
   AC_DEFINE(HAVE_GSF, 1, [Define to 1 if you have libgsf (OLE and ODF) support])
fi


dnl Check for poppler support
AC_ARG_WITH(poppler, [  --without-poppler        disable PDF support])
have_pdf=no
if test x$with_poppler != xno; then
    PKG_CHECK_MODULES(POPPLER, poppler-glib >= $POPPLER_REQ, have_pdf=yes, have_pdf=no)
fi
if test "x$have_pdf" = "xyes"; then
   AC_DEFINE(HAVE_PDF, 1, [Define to 1 if you have PDF support])
   POPPLER_PREFIX=`pkg-config --variable=prefix poppler-glib`
   POPPLER_VERSION=`pkg-config --modversion poppler-glib`
   AC_SUBST(POPPLER_VERSION)
   AC_SUBST(POPPLER_PREFIX)
fi


dnl =====================
dnl     Google Test
dnl =====================

# Configure pthreads.
# ACX_PTHREAD([have_pthread=yes])

# Define gtest variables
if test "x$have_pthread" = "xyes"; then
GTEST_CPPFLAGS="-DGTEST_HAS_PTHREAD=1"
GTEST_CXXFLAGS="$PTHREAD_CFLAGS"
GTEST_LDFLAGS=
GTEST_LIBS="$PTHREAD_LIBS"
else
GTEST_CPPFLAGS="-DGTEST_HAS_PTHREAD=0"
GTEST_CXXFLAGS=
GTEST_LDFLAGS=
GTEST_LIBS=
fi
AC_SUBST([GTEST_CPPFLAGS])
AC_SUBST([GTEST_CXXFLAGS])
AC_SUBST([GTEST_LDFLAGS])
AC_SUBST([GTEST_LIBS])

AC_MSG_RESULT([
Google Test is now configured (for \"make check\")

    GTEST_CPPFLAGS  : $GTEST_CPPFLAGS
    GTEST_CXXFLAGS  : $GTEST_CXXFLAGS
    GTEST_LDFLAGS   : $GTEST_LDFLAGS
    GTEST_LIBS      : $GTEST_LIBS
])

dnl =============================
dnl Checks for library functions
dnl =============================

AC_FUNC_MMAP

dnl ================================================================
dnl Python
dnl ================================================================

AC_MSG_CHECKING([whether Python support is requested])
AC_ARG_ENABLE([python],
    AS_HELP_STRING([--enable-python],[Enable python support]),
    [enable_python=$enableval have_python=$enableval],
    [enable_python=autodetect have_python=yes])
AC_MSG_RESULT([$enable_python])

if test "x$have_python" != "xno"; then
    AM_PATH_PYTHON([$PYTHON_REQ],[],[no])
    if test "x$PYTHON" = "x:"; then
        have_python=no
    fi
fi

if test "x$have_python" != "xno"; then
    AM_CHECK_PYTHON_HEADERS([],[have_python=no])
fi

if test "x$have_python" != "xno"; then
    PY_PREFIX=`$PYTHON -c 'import sys ; print sys.prefix'`
    PY_EXEC_PREFIX=`$PYTHON -c 'import sys ; print sys.exec_prefix'`
    PYTHON_LIBS="-lpython$PYTHON_VERSION"
    PYTHON_LIB_LOC="-L$PY_EXEC_PREFIX/lib/python$PYTHON_VERSION/config"
    PYTHON_CFLAGS="-I$PY_PREFIX/include/python$PYTHON_VERSION"
    PYTHON_MAKEFILE="$PY_EXEC_PREFIX/lib/python$PYTHON_VERSION/config/Makefile"
    PYTHON_LOCALMODLIBS=`sed -n -e 's/^LOCALMODLIBS=\(.*\)/\1/p' $PYTHON_MAKEFILE`
    PYTHON_BASEMODLIBS=`sed -n -e 's/^BASEMODLIBS=\(.*\)/\1/p' $PYTHON_MAKEFILE`
    PYTHON_OTHER_LIBS=`sed -n -e 's/^LIBS=\(.*\)/\1/p' $PYTHON_MAKEFILE`
    PYTHON_EXTRA_LIBS="$PYTHON_LOCALMODLIBS $PYTHON_BASEMODLIBS $PYTHON_OTHER_LIBS"
    AC_SUBST([PYTHON_LIBS])
    AC_SUBST([PYTHON_LIB_LOC])
    AC_SUBST([PYTHON_CFLAGS])
    AC_SUBST([PYTHON_EXTRA_LIBS])

    dnl FIXME: do we really need this test?
    AC_MSG_CHECKING([whether we can build a shared library depending on libpython])
    rm -rf testpython
    mkdir testpython
    cd testpython
    cat > testpython.c <<EOF
#include <Python.h>
int testpython (void)
{
Py_Exit (0);
}
EOF

    if ${CC} $PYTHON_CFLAGS $PYTHON_LIBS $PYTHON_EXTRA_LIBS -fPIC -shared -o testpython.so testpython.c -Wl,-soname,testpython.so >/dev/null 2>&1 && \
        ( objdump --headers --private-headers testpython.so | grep 'testpython' ) >/dev/null 2>&1; then
        result=yes
    else
        result=no
        have_python=no
    fi
    cd ..
    rm -rf testpython
    AC_MSG_RESULT([$result])
fi

if test "x$have_python" != "xyes"; then
    if test "x$enable_python" = "xyes"; then
        AC_MSG_ERROR([Python not found])
    elif test "x$enable_python" = "xautodetect"; then
        enable_python=no
        AC_MSG_WARN([Python not found, disabling python support])
    fi
elif test "x$enable_python" != "xno"; then
    enable_python=yes
    AC_DEFINE([HAVE_PYTHON],[1],[Define to compile with python support])
fi

AM_CONDITIONAL([HAVE_PYTHON],[test "x$enable_python" = "xyes"])


dnl =====================
dnl Set stuff in config.h
dnl =====================

dnl Get the prefix
if test "x${prefix}" = "xNONE"; then
  PREFIX="${ac_default_prefix}"
  AC_DEFINE_UNQUOTED(PREFIX, "${ac_default_prefix}", [definition of PREFIX])
else
  PREFIX="${prefix}"
  AC_DEFINE_UNQUOTED(PREFIX, "${prefix}", [definition of PREFIX])
fi
AC_SUBST(PREFIX)


dnl Set PACKAGE_LOCALE_DIR in config.h.
AC_DEFINE_UNQUOTED(PACKAGE_LOCALE_DIR, "${PREFIX}/${DATADIRNAME}/locale", [definition of PACKAGE_LOCALE_DIR])


dnl Set PIXMAPS_DIR in config.h.
AC_DEFINE_UNQUOTED(PIXMAPS_DIR, "${PREFIX}/share/pixmaps/${PACKAGE}", [pixmaps location])


dnl Set GNOME_PREFIX in config.h.
GNOME_PREFIX_TMP=`pkg-config --variable=prefix libgnome-2.0`
AC_DEFINE_UNQUOTED(GNOME_PREFIX, "$GNOME_PREFIX_TMP", "")


dnl Set HELP_DIR in config.h.
AC_DEFINE_UNQUOTED(HELP_DIR, "${PREFIX}/share/gnome/help/${PACKAGE}", "")


PLUGIN_LIBTOOL_FLAGS="-module -avoid-version"
AC_SUBST(PLUGIN_LIBTOOL_FLAGS)

dnl =====================
dnl Check for binary
dnl =====================
AC_CHECK_PROG(HAVE_UPDATE_MIME_DATABASE, update-mime-database, "yes", "no")
AC_SUBST(HAVE_UPDATE_MIME_DATABASE)


dnl =====================
dnl Write some output
dnl =====================

AC_OUTPUT([
Makefile
data/gnome-commander.ebuild
data/gnome-commander.spec
data/gnome-commander.desktop.in
data/Makefile
doc/Makefile
libgcmd/Makefile
pixmaps/Makefile
pixmaps/device-icons/Makefile
pixmaps/file-type-icons/Makefile
pixmaps/mime-icons/Makefile
plugins/Makefile
plugins/fileroller/Makefile
plugins/python/Makefile
plugins/python/md5sum/Makefile
plugins/python/sha1sum/Makefile
plugins/python/apply-patch/Makefile
plugins/test/Makefile
po/Makefile.in
src/Makefile
src/dialogs/Makefile
src/tags/Makefile
src/intviewer/Makefile
tests/Makefile
README
])



echo ""
echo ""
echo "=========================================="
echo " Ready to build GNOME Commander ${VERSION}"
echo "=========================================="
echo ""
echo "The following settings will be used:"
echo ""
echo "  host           : ${host}"
echo "  prefix         : ${prefix}"
echo "  module support : ${GMODULE_AVAIL}"
echo "  compiler       : ${CC}"
echo "  CFLAGS         : ${CFLAGS}"
echo "  LDFLAGS        : ${LDFLAGS}"
echo ""
echo "  Python plugins support: ${enable_python}"
echo ""
echo ""
echo "Optional file metadata support:"
echo ""
echo "  Exif support   : ${have_exiv2}"
echo "  IPTC support   : ${have_exiv2}"
echo "  ID3 support    : ${have_taglib}"
echo "  Vorbis support : ${have_taglib}"
echo "  APE support    : ${have_taglib}"
echo "  FLAC support   : ${have_taglib}"
echo "  OLE2 support   : ${have_gsf}"
echo "  ODF support    : ${have_gsf}"
echo "  PDF support    : ${have_pdf}"
echo "  SAMBA support  : ${have_samba}"
echo ""
echo ""
echo "The following libraries will be used:"
echo ""
echo "  glib           : ${GLIB_VERSION}	in ${GLIB_PREFIX}"
echo "  gtk+           : ${GTK_VERSION}	in ${GTK_PREFIX}"
echo "  gnome          : ${GNOME_VERSION}	in ${GNOME_PREFIX}"
echo "  gnomeui        : ${GNOMEUI_VERSION}	in ${GNOMEUI_PREFIX}"
echo "  gnome-vfs      : ${GNOMEVFS_VERSION}	in ${GNOMEVFS_PREFIX}"
echo "  gnome-keyring  : ${GNOME_KEYRING_VERSION}	in ${GNOME_KEYRING_PREFIX}"
echo "  libUnique      : ${UNIQUE_VERSION}	in ${UNIQUE_PREFIX}"
if test "x$have_pdf" = "xyes"; then
echo "  poppler-glib   : ${POPPLER_VERSION}  	in ${POPPLER_PREFIX}"
fi
if test "x$have_python" = "xyes"; then
echo "  python         : ${PYTHON_VERSION}  	in ${PY_EXEC_PREFIX}"
fi
echo ""
echo ""
echo "Type 'make' to build $PACKAGE-$VERSION and then 'make install' to install"
echo ""
