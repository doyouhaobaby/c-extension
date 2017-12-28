dnl $Id$
dnl config.m4 for extension qys

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(qys, for qys support,
dnl Make sure that the comment is aligned:
dnl [  --with-qys             Include qys support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(qys, whether to enable qys support,
Make sure that the comment is aligned:
[  --enable-qys           Enable qys support])

if test "$PHP_QYS" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-qys -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/qys.h"  # you most likely want to change this
  dnl if test -r $PHP_QYS/$SEARCH_FOR; then # path given as parameter
  dnl   QYS_DIR=$PHP_QYS
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for qys files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       QYS_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$QYS_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the qys distribution])
  dnl fi

  dnl # --with-qys -> add include path
  dnl PHP_ADD_INCLUDE($QYS_DIR/include)

  dnl # --with-qys -> check for lib and symbol presence
  dnl LIBNAME=qys # you may want to change this
  dnl LIBSYMBOL=qys # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $QYS_DIR/$PHP_LIBDIR, QYS_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_QYSLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong qys lib version or lib not found])
  dnl ],[
  dnl   -L$QYS_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(QYS_SHARED_LIBADD)

  PHP_NEW_EXTENSION(qys, qys.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
