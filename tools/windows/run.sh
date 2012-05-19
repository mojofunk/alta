#!/bin/bash

WIN32_ROOT=winmojo

if test ! -d $WIN32_ROOT
then
	echo "Win32 root does not exist"
	exit 1
fi

BUILD_DIR=build/src

GMOJO_PATH=share

export GMOJO_PATH

MOJO_PATH=\
$BUILD_DIR/modules/AudioFileModule/sndfile:\
$BUILD_DIR/modules/AudioDriverModule/jack:\
$BUILD_DIR/modules/AudioEffectModule/ladspa:\
$BUILD_DIR/modules/ArchiveModule/dummy:\
$BUILD_DIR/modules/ArchiveModule/xml

EXECUTABLE="build/src/mojo-gtkmm/gmojo.exe"
cp $EXECUTABLE winmojo
cd winmojo

wine gmojo.exe