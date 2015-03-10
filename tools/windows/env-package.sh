#!/bin/bash

# get these from the single place that versions are defined
PROGRAM_MAJOR_VERSION=0
PROGRAM_MINOR_VERSION=1
PROGRAM_MICRO_VERSION=0
PROGRAM_FULL_VERSION=${PROGRAM_MAJOR_VERSION}.${PROGRAM_MINOR_VERSION}.${PROGRAM_MICRO_VERSION}

LOWERCASE_DIRNAME=alta
# see wscript 'lwrcase_dirname' used for lib/ardour3 and share/ardour3
STATEFILE_SUFFIX=alta # see filename_extensions.cc

# derived variables
PRODUCT_ID=${PROGRAM_NAME}${PROGRAM_MAJOR_VERSION}
PRODUCT_EXE=${PROGRAM_NAME}-${PROGRAM_FULL_VERSION}.exe
PRODUCT_ICON=${PRODUCT_NAME}.ico

# Figure out the Build Type
if [ x$DEBUG = xT ]; then
    PACKAGE_DIR="$PRODUCT_NAME-${PROGRAM_FULL_VERSION}-$ARCH-dbg"
else
    PACKAGE_DIR="$PRODUCT_NAME-${PROGRAM_FULL_VERSION}-$ARCH"
fi

PACKAGE_BIN_DIR=$PACKAGE_DIR/bin
PACKAGE_LIB_DIR=$PACKAGE_DIR/lib

if grep -q "BUILD_TESTS = True" $BUILD_CACHE_FILE; then
    WITH_TESTS=1
fi

PACKAGE_DATA_DIR=$PACKAGE_DIR/share/alta
