#!/bin/bash

. ./env.sh

cd $BASE || exit 1
scan-build ./waf configure --with-tests "$@"
