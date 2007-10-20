#!/bin/sh

# --log_level=test_suite

. gmojo_env.sh

RTG_TEST_DIR=$BUILD_DIR/rtg/tests

echo "Running test cases for rtg"

$RTG_TEST_DIR/test_graph "$@"

ARK_TEST_DIR=$BUILD_DIR/ark/tests

echo "Running test cases for ark"

$ARK_TEST_DIR/test_dummy_archive "$@"

GLEAM_TEST_DIR=$BUILD_DIR/libgleam/tests

echo "Running test cases for gleam"

$GLEAM_TEST_DIR/test_filesystem_paths "$@"
