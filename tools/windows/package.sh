#!/bin/bash

. ./env-mingw.sh

. ./print-env.sh

if [ -z "$DLLS" ]; then
	echo "ERROR: DLLS variable is not defined..."
	exit 1
fi

cd $BASE || exit 1

if [ -d $PACKAGE_DIR ]; then
	echo "Removing old package directory structure ..."
	rm -rf $PACKAGE_DIR || exit 1
fi

. $TOOLS_DIR/package-alta.sh

. $TOOLS_DIR/package-gtk.sh

cp $TOOLS_DIR/README $PACKAGE_DIR

echo "Copying mingw shared libraries to $PACKAGE_BIN_DIR ..."

for i in $DLLS;
do
	copydll "$i" "$PACKAGE_BIN_DIR" || exit 1
done

. $TOOLS_DIR/package-jack.sh

if [ x$DEBUG = xT ]; then

    . $TOOLS_DIR/package-source.sh

	. $TOOLS_DIR/package-lv2-tools.sh

	#echo "Copying any debug files to $PACKAGE_DIR ..."
	#cp $MINGW_ROOT/bin/*.debug $PACKAGE_DIR

	echo "Copying gdb and config files to $PACKAGE_DIR ..."
	cp $MINGW_ROOT/bin/gdb.exe $PACKAGE_BIN_DIR
	. $TOOLS_DIR/make-debug-script.sh

else
	echo "Optimized build Stripping executable ..."
	find $PACKAGE_DIR -type f -name "*.exe*" | xargs $STRIP
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
