#! /bin/bash

# This is not a standalone script

if [ x$DEBUG = xT ]; then

	echo "Copying source files to $PACKAGE_DIR/src ..."
	cp -r $BASE/src $PACKAGE_DIR
fi
