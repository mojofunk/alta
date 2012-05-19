#!/bin/sh

. ./env.sh

cd $BASE || exit 1
exec nemiver $EXECUTABLE "$@"
