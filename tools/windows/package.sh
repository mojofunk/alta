#!/bin/bash

. ./mingw-env.sh

. ./print-env.sh

cd $BASE || exit 1

if ! test -f $BUILD_CACHE_FILE; then
	echo "ERROR: $APPNAME is not configured and built yet..."
	exit 1
fi

if [ -d $PACKAGE_DIR ]; then
	echo "Removing old package directory structure ..."
	rm -rf $PACKAGE_DIR || exit 1
fi

./waf --destdir=$PACKAGE_DIR install || exit 1

echo "Copying UI files $PACKAGE_DIR ..."

cp -r $BASE/data $PACKAGE_DIR

echo "Moving dll's and executable to $PACKAGE_DIR ..."

mv $PACKAGE_DIR/bin/*.dll $PACKAGE_DIR || exit 1
mv $PACKAGE_DIR/bin/*.exe $PACKAGE_DIR || exit 1

echo "Deleting import libs ..."

rm $PACKAGE_DIR/lib/*dll.a

if test x$WITH_TESTS != x ; then
	echo "Copying tests and test data to $PACKAGE_DIR ..."
	#cp $BUILD_DIR/libs/pbd/run-tests.exe $PACKAGE_DIR/pbd-run-tests.exe
	#cp -r $BASE/libs/pbd/test $ARDOUR_DATA_DIR/pbd_testdata

	#cp $BUILD_DIR/libs/evoral/run-tests.exe $PACKAGE_DIR/evoral-run-tests.exe
	#mkdir -p $PACKAGE_DIR/test/testdata
	#cp -r $BASE/libs/evoral/test/testdata/TakeFive.mid $PACKAGE_DIR/test/testdata
fi


echo "Copying mingw config files to $PACKAGE_DIR ..."
# just copy it all for now
cp -r $MINGW_ROOT/etc $PACKAGE_DIR

cp -r $MINGW_ROOT/lib/gtk-2.0 $PACKAGE_DIR/lib
cp -r $MINGW_ROOT/lib/gdk-pixbuf-2.0 $PACKAGE_DIR/lib
cp $TOOLS_DIR/loaders.cache $PACKAGE_DIR/lib/gdk-pixbuf-2.0/2.10.0/loaders.cache

mkdir -p $PACKAGE_DIR/lib/pango/1.6.0/modules
cp -r $MINGW_ROOT/lib/pango/1.6.0/modules/*.dll $PACKAGE_DIR/lib/pango/1.6.0/modules
cp $TOOLS_DIR/pango.modules $PACKAGE_DIR/etc/pango

#/usr/i686-pc-mingw32/sys-root/mingw/bin/boost_signals-gcc46-mt-1_47.dll
#/usr/i686-pc-mingw32/sys-root/mingw/bin/boost_unit_test_framework-gcc46-mt-1_47.dll


DLLS='
jack-0.dll
jackserver-0.dll
libatk-1.0-0.dll
libatkmm-1.6-1.dll
boost_filesystem-gcc46-mt-1_47.dll
boost_system-gcc46-mt-1_47.dll
libcairo-2.dll
libcairo-gobject-2.dll
libcairomm-1.0-1.dll
libcairo-script-interpreter-2.dll
libcppunit-1-12-1.dll
libcrypto-10.dll
libcurl-4.dll
libexpat-1.dll
libfftw3-3.dll
libfftw3f-3.dll
libfontconfig-1.dll
libfreetype-6.dll
libgailutil-18.dll
libgcc_s_sjlj-1.dll
libgdkmm-2.4-1.dll
libgdk_pixbuf-2.0-0.dll
libgdk-win32-2.0-0.dll
libgio-2.0-0.dll
libgiomm-2.4-1.dll
libglib-2.0-0.dll
libglibmm-2.4-1.dll
libglibmm_generate_extra_defs-2.4-1.dll
libgmodule-2.0-0.dll
libgdk-3-0.dll
libgtk-3-0.dll
libgtkmm-3.0-1.dll
libgdkmm-3.0-1.dll
libgoocanvas-2.0-9.dll
libgoocanvasmm-2.0-6.dll
libgnurx-0.dll
libgobject-2.0-0.dll
libgthread-2.0-0.dll
libgtk-win32-2.0-0.dll
libiconv-2.dll
iconv.dll
libFLAC-8.dll
libogg-0.dll
libvorbis-0.dll
libvorbisenc-2.dll
libffi-5.dll
libidn-11.dll
libintl-8.dll
libpango-1.0-0.dll
libpangocairo-1.0-0.dll
libpangoft2-1.0-0.dll
libpangomm-1.4-1.dll
libpangowin32-1.0-0.dll
libpixman-1-0.dll
libpng14-14.dll
libsamplerate-0.dll
libsigc-2.0-0.dll
libsndfile-1.dll
libssh2-1.dll
libssl-10.dll
libstdc++-6.dll
libxml2-2.dll
pthreadGC2.dll
zlib1.dll
'

echo "Copying mingw shared libraries to $PACKAGE_DIR ..."

for i in $DLLS;
do
cp $MINGW_ROOT/bin/$i $PACKAGE_DIR
done

echo "Copying JACK server and drivers to $PACKAGE_DIR ..."

cp $MINGW_ROOT/bin/jackd.exe $PACKAGE_DIR
cp -r $MINGW_ROOT/bin/jack $PACKAGE_DIR
cp $MINGW_ROOT/bin/libportaudio-2.dll $PACKAGE_DIR

if test x$DEBUG != x ; then

	PACKAGE_SRC_DIR=$PACKAGE_DIR/src
	echo "Copying source files to $PACKAGE_SRC_DIR ..."
	mkdir -p $PACKAGE_SRC_DIR/libs
	cp -r $BASE/src $PACKAGE_DIR
	
	echo "Copying JACK utility programs to $PACKAGE_DIR ..."
	cp $MINGW_ROOT/bin/jack_*.exe $PACKAGE_DIR

	echo "Copying any debug files to $PACKAGE_DIR ..."
	cp $MINGW_ROOT/bin/*.debug $PACKAGE_DIR

	echo "Copying gdb to $PACKAGE_DIR ..."
	cp $MINGW_ROOT/bin/gdb.exe $PACKAGE_DIR

	echo "Copying .gdbinit to $PACKAGE_DIR ..."
	cp $TOOLS_DIR/gdbinit $PACKAGE_DIR/.gdbinit

	echo "Copying Gtk demo to $PACKAGE_DIR ..."
	cp $MINGW_ROOT/bin/gtk-demo.exe $PACKAGE_DIR
else
	echo "Optimized build Stripping executable ..."
	#find $PACKAGE_DIR -type f -name "*.exe" | xargs $STRIP
	#$STRIP $PACKAGE_DIR/ardour-3.0.exe
	echo "Stripping libraries ..."
	find $PACKAGE_DIR -type f -name "*.dll*" | xargs $STRIP
fi

if [ "$1" == "--tarball" ]; then
	echo "Creating tarball from $PACKAGE_DIR ..."
	cd $BASE || exit 1
	tar -cvJf $PACKAGE_DIR.tar.xz $PACKAGE_DIR
fi

if [ "$1" == "--zip" ]; then
	echo "Creating zip file from $PACKAGE_DIR ..."
	cd $BASE || exit 1
	zip -r $PACKAGE_DIR.zip $PACKAGE_DIR
fi