#!/bin/bash

ENV_SCRIPT_PATH=$( cd $(dirname $0) ; pwd -P )
TOP_LEVEL_PATH="$ENV_SCRIPT_PATH/../.."

BUILD_DIR="$TOP_LEVEL_PATH/waf-build"
BUILD_CACHE_FILE="$BUILD_DIR/c4che/_cache.py"
TOOLS_DIR="$TOP_LEVEL_PATH/tools/linux"

APPNAME=`grep -m 1 '^APPNAME' $TOP_LEVEL_PATH/wscript | awk '{print $3}' | sed "s/'//g"`
VERSION=`grep -m 1 '^VERSION' $TOP_LEVEL_PATH/wscript | awk '{print $3}' | sed "s/'//g"`

PROGRAM_NAME=Alta

EXECUTABLE="$BUILD_DIR/src/gtkmm_ui/$PROGRAM_NAME"

export ALTA_PATH="$TOP_LEVEL_PATH/data"
export MOJO_TEST_PATH=$TOP_LEVEL_PATH/data

MOJO_PATH=\
$BUILD_DIR/src/mojo/archive/xml:\
$BUILD_DIR/src/mojo/archive/dummy:\
$BUILD_DIR/src/mojo/audio_effect/ladspa:\
$BUILD_DIR/src/mojo/audio_file/sndfile:\
$BUILD_DIR/src/mojo/audio_driver/jack:\
$BUILD_DIR/src/mojo/audio_driver/portaudio:\
$BUILD_DIR/src/mojo/midi_driver/portmidi:

export MOJO_PATH

GLEAM_LIBRARY_PATH=$BUILD_DIR/src/gleam

MOJO_LIBRARY_PATH=$BUILD_DIR/src/mojo/core:\
$BUILD_DIR/src/mojo/application:\
$BUILD_DIR/src/mojo/engine:\
$BUILD_DIR/src/mojo/archive:\
$BUILD_DIR/src/mojo/audio_driver:\
$BUILD_DIR/src/mojo/audio_effect:\
$BUILD_DIR/src/mojo/audio_file:\
$BUILD_DIR/src/mojo/midi_driver:

MOJO_TEST_LIBRARY_PATH=$BUILD_DIR/src/mojo/tests:

THIRD_PARTY_LIBRARY_PATH=\
$BUILD_DIR/src/third_party/fmt

export LD_LIBRARY_PATH=\
$GLEAM_LIBRARY_PATH:\
$MOJO_LIBRARY_PATH:\
$MOJO_TEST_LIBRARY_PATH:\
$THIRD_PARTY_LIBRARY_PATH:
