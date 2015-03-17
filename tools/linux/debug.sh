#!/bin/sh

. ./env.sh

cd $BASE || exit 1
exec gdb $EXECUTABLE "$@"
