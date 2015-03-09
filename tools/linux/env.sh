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

PROGRAM_NAME=Alta

EXECUTABLE="$BUILD_DIR/src/gtkmm_ui/$PROGRAM_NAME"

export GMOJO_PATH=data
export MOJO_TEST_PATH=$BASE/data

MOJO_PATH=\
$BUILD_DIR/src/mojo/archive/xml:\
$BUILD_DIR/src/mojo/audio_effect/ladspa:\
$BUILD_DIR/src/mojo/audio_file/sndfile:\
$BUILD_DIR/src/mojo/audio_driver/jack:

export MOJO_PATH

GLEAM_LIBRARY_PATH=$BUILD_DIR/src/gleam

MOJO_LIBRARY_PATH=$BUILD_DIR/src/mojo/core:\
$BUILD_DIR/src/mojo/application:\
$BUILD_DIR/src/mojo/engine:\
$BUILD_DIR/src/mojo/archive:\
$BUILD_DIR/src/mojo/audio_driver:\
$BUILD_DIR/src/mojo/audio_effect:\
$BUILD_DIR/src/mojo/audio_file:

MOJO_TEST_LIBRARY_PATH=$BUILD_DIR/src/mojo/tests:

export LD_LIBRARY_PATH=\
$GLEAM_LIBRARY_PATH:\
$MOJO_LIBRARY_PATH:\
$MOJO_TEST_LIBRARY_PATH:
