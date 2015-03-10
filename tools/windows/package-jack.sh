#! /bin/bash

# This is not a standalone script

if test x$WITH_JACK != x; then
	echo "Copying JACK server and drivers to $PACKAGE_BIN_DIR ..."
	cp $MINGW_ROOT/bin/jackd.exe $PACKAGE_BIN_DIR
	cp -r $MINGW_ROOT/bin/jack $PACKAGE_BIN_DIR
fi

if [ x$DEBUG = xT ]; then

	if test x$WITH_JACK != x; then
		echo "Copying JACK utility programs to $PACKAGE_BIN_DIR ..."
		cp $MINGW_ROOT/bin/jack_*.exe $PACKAGE_BIN_DIR
	fi
fi
