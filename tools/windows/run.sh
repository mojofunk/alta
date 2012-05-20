#!/bin/bash

. mingw-env.sh

cd $BASE

if test ! -d $PACKAGE_DIR; then
	echo "Win32 package directory does not exist"
	exit 1
fi

export GMOJO_PATH="$BASE/$PACKAGE_DIR/data"

MOJO_PATH=\
$BUILD_DIR/modules/AudioFileModule/sndfile:\
$BUILD_DIR/modules/AudioDriverModule/jack:\
$BUILD_DIR/modules/AudioEffectModule/ladspa:\
$BUILD_DIR/modules/ArchiveModule/dummy:\
$BUILD_DIR/modules/ArchiveModule/xml

cd $PACKAGE_DIR

wine gmojo.exe
