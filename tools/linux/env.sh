#!/bin/bash

BASE=$(readlink -f $0)
BASE=$(dirname $BASE) # up one
BASE=$(dirname $BASE) # up one more
BASE=$(dirname $BASE) # up one more

BUILD_DIR=$BASE/build
BUILD_CACHE_FILE=$BUILD_DIR/c4che/_cache.py
TOOLS_DIR=$BASE/tools/linux

APPNAME=`grep -m 1 '^APPNAME' $BASE/wscript | awk '{print $3}' | sed "s/'//g"`
VERSION=`grep -m 1 '^VERSION' $BASE/wscript | awk '{print $3}' | sed "s/'//g"`

EXECUTABLE="$BUILD_DIR/src/mojo-gtkmm/gmojo"

export GMOJO_PATH=data
export MOJO_TEST_PATH=$BASE/data

MOJO_PATH=\
$BUILD_DIR/src/modules/AudioFileModule/sndfile:\
$BUILD_DIR/src/modules/AudioDriverModule/jack:\
$BUILD_DIR/src/modules/AudioEffectModule/ladspa:\
$BUILD_DIR/src/modules/ArchiveModule/dummy:\
$BUILD_DIR/src/modules/ArchiveModule/xml

export MOJO_PATH

GLEAM_LIBRARY_PATH=$BUILD_DIR/src/gleam
MOJO_LIBRARY_PATH=$BUILD_DIR/src/mojo
MOJO_MODULE_LIBRARY_PATH=$BUILD_DIR/src/modules

export LD_LIBRARY_PATH=\
$GLEAM_LIBRARY_PATH:\
$MOJO_LIBRARY_PATH:\
$MOJO_MODULE_LIBRARY_PATH:\
