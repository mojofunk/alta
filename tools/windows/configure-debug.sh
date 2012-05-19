#!/bin/bash

. ./mingw-env.sh

. ./print-env.sh

cd $BASE || exit 1
./waf configure --prefix="/" --bindir="/" --configdir="/share" --with-tests --with-target-platform=mingw "$@"