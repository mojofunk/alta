#! /bin/bash

# This is not a standalone script

if test x$WITH_LV2 != x; then
	echo "Copying LV2 utility programs to $PACKAGE_BIN_DIR ..."
	cp $MINGW_ROOT/bin/lilv-bench.exe $PACKAGE_BIN_DIR
	cp $MINGW_ROOT/bin/lv2info.exe $PACKAGE_BIN_DIR
	cp $MINGW_ROOT/bin/lv2ls.exe $PACKAGE_BIN_DIR
fi

