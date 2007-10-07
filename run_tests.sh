#!/bin/sh

# --log_level=test_suite

. gmojo_env.sh

GLEAM_TEST_DIR=$BUILD_DIR/libgleam/tests

exec $GLEAM_TEST_DIR/test_filesystem_paths "$@"
