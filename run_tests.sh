#!/bin/sh

# --log_level=test_suite

. gmojo_env.sh

RTG_TEST_DIR=$BUILD_DIR/rtg/tests

$RTG_TEST_DIR/test_graph "$@"

GLEAM_TEST_DIR=$BUILD_DIR/libgleam/tests

$GLEAM_TEST_DIR/test_filesystem_paths "$@"
