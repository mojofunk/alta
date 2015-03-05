#!/bin/bash

. ./env.sh

cd $BASE || exit 1
./waf configure --enable-amalgamation --with-gtkmm-ui "$@"
