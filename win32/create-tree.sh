#!/bin/sh

MINGW_ROOT='/usr/i686-pc-mingw32/sys-root/mingw'
WIN32_ROOT='winmojo'

rm -rf $WIN32_ROOT 

mkdir $WIN32_ROOT 

cp build/default/src/gleam/libgleam.dll $WIN32_ROOT
cp build/default/src/mojo/libmojo.dll $WIN32_ROOT
cp -r data $WIN32_ROOT

# just copy it all for now
cp -r $MINGW_ROOT/etc $WIN32_ROOT

mkdir $WIN32_ROOT/lib
cp -r $MINGW_ROOT/lib/gtk-2.0 $WIN32_ROOT/lib

mkdir -p $WIN32_ROOT/lib/pango/1.6.0/modules
cp -r $MINGW_ROOT/lib/pango/1.6.0/modules/*.dll $WIN32_ROOT/lib/pango/1.6.0/modules
cp $MINGW_ROOT/etc/pango/pango.modules $WIN32_ROOT/etc/pango

DLLS='
libintl-8.dll
libatk-1.0-0.dll
libatkmm-1.6-1.dll
libglib-2.0-0.dll
libglibmm-2.4-1.dll
libgthread-2.0-0.dll
libgobject-2.0-0.dll
libgmodule-2.0-0.dll
libgio-2.0-0.dll
libgiomm-2.4-1.dll
libgdk-win32-2.0-0.dll
libgdkmm-2.4-1.dll
libcairo-2.dll
libcairomm-1.0-1.dll
libpangocairo-1.0-0.dll
libpangomm-1.4-1.dll
libgtk-win32-2.0-0.dll
libgtkmm-2.4-1.dll
libpango-1.0-0.dll
libgoocanvas-3.dll
libgoocanvasmm-1.0-5.dll
libsigc-2.0-0.dll
libgcc_s_sjlj-1.dll
'

#for i in $DLLS;
#do
cp $MINGW_ROOT/bin/* $WIN32_ROOT
#done
